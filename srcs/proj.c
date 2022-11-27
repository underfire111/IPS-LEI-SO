#include "proj.h"

#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void	kill_all(int *pids, int num_process);
void	generate_results(pt_items items, pt_bag bag, pt_bag result, sem_t *update);
void	update_bag_status(pt_items items, pt_bag bag, int index);

struct s_stats
{
	size_t	best_iterator;
	time_t	best_time;
};

void	proj(pt_info info, pt_items items, pt_bag bag)
{
	int *	pids;
	sem_t *	update;
	pt_bag	result;

	sem_unlink("update");
	update = sem_open("update", O_CREAT, 0644, 1);
	result = (pt_bag)mmap(NULL, sizeof(struct s_bag), PROT_READ |
		PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*result = *bag;
	pids = (int *)malloc(sizeof(int) * info->num_processes);
	for (int i = 0; i < info->num_processes; i++)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			generate_results(items, bag, result, update);
	}
	sem_close(update);
	sleep(info->time_limit);
	kill_all(pids, info->num_processes);
	printf("best_result = %d | %d\n", result->curr_price, result->max_weight);
	for (int i = 0; i < info->num_items; i++)
		printf("%d, ", bag->items[i]);
	printf("\n");
}

void	kill_all(int *pids, int num_process)
{
	int	status;

	for (int i = 0; i < num_process; i++)
	{
		kill(pids[i], SIGKILL);
		wait(&status);
	}
	free(pids);
}

void	generate_results(pt_items items, pt_bag bag, pt_bag result, sem_t *update)
{
	int	iterator;
	int	r_index;

	srand(getpid() + time(NULL));
	while (1)
	{
		r_index = rand() % items->size;
		update_bag_status(items, bag, r_index);
		sem_wait(update);
		if (bag->curr_price > result->curr_price)
			*result = *bag; 
		sem_post(update);
	}
}

void	update_bag_status(pt_items items, pt_bag bag, int index)
{
	int	curr_weight;

	if (bag->items[index] == 0)
	{
		curr_weight = bag->curr_weight + items->item[index].weight;
		if (curr_weight <= bag->max_weight)
		{
			bag->items[index] = 1;
			bag->curr_price += items->item[index].price;
			bag->curr_weight = curr_weight;
		}
	}
	else
	{
		bag->items[index] = 0;
		bag->curr_price -= items->item[index].price;
		bag->curr_weight -= items->item[index].weight;
	}
}
