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

void	set_shared_memory(pt_bag bag, pt_bag *result, t_stats **stats);
void	signalize_all(int signum);
void	signal_handler_parent(int signum, siginfo_t *siginfo, void *context);
void	signal_handler_child(int signum, siginfo_t *siginfo, void *context);
void	generate_results(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats);
void	update_bag_status(pt_items items, pt_bag bag, int index);

typedef struct	sigaction sigaction_t;

pt_info	_info;

void	proj(pt_info temp, pt_items items, pt_bag bag)
{
	sigaction_t	sa;
	t_stats *	stats;
	sem_t *		update;
	pt_bag		result;

	_info = temp;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler_parent;
	sigaction(SIGUSR1, &sa, NULL);
	sem_unlink("update");
	update = sem_open("update", O_CREAT, 0644, 1);
	set_shared_memory(bag, &result, &stats);
	for (int i = 0; i < _info->num_processes; i++)
	{
		_info->cpids[i] = fork();
		if (_info->cpids[i] == 0)
			generate_results(items, bag, result, update, stats);
	}
	sem_close(update);
	sleep(_info->time_limit);
	signalize_all(SIGKILL);

	printf("num_iterations = %d, time = %d seconds\n", stats->iterator, 
		(stats->time - stats->begin));
	printf("best_result = %d | %d\n", result->curr_price, result->curr_weight);
	for (int i = 0; i < _info->num_items; i++)
		printf("%d ", result->items[i]);
	printf("\n");

}

void	set_shared_memory(pt_bag bag, pt_bag *result, t_stats **stats)
{
	char *	keys;

	keys = (char *)mmap(NULL, sizeof(char) * _info->num_items + 1, PROT_READ |
		PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	for (int i = 0; i < _info->num_items; i++)
		keys[i] = 1;

	(*result) = (pt_bag)mmap(NULL, sizeof(struct s_bag), PROT_READ |
		PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	(*(*result)) = *bag;
	(*(*result)).items = keys;

	(*stats) = (t_stats *)mmap(NULL, sizeof(t_stats), PROT_READ |
			PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	(*(*stats)) = __init_stats();
}

void	signalize_all(int signum)
{
	int	status;

	for (int i = 0; i < _info->num_processes; i++)
	{
		kill(_info->cpids[i], signum);
		wait(&status);
	}
	if (signum == SIGKILL)
		free(_info->cpids);
}

void	generate_results(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats)
{
	sigaction_t	sa;
	size_t		iterator;
	int			r_index;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &signal_handler_child;
	sigaction(SIGUSR1, &sa, NULL);
	srand(getpid() + time(NULL));
	iterator = 0;
	while (++iterator)
	{
		r_index = rand() % items->size;
		update_bag_status(items, bag, r_index);
		sem_wait(update);
		if (bag->curr_price > result->curr_price)
		{
			result->curr_price = bag->curr_price;
			result->curr_weight = bag->curr_weight; 
			for (size_t i = 0; i < items->size; i++)
				result->items[i] = bag->items[i];
			stats->iterator = iterator;
			stats->time = time(NULL);
		}
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
			bag->items[index]++;
			bag->curr_price += items->item[index].price;
			bag->curr_weight = curr_weight;
		}
	}
	else
	{
		bag->items[index]--;
		bag->curr_price -= items->item[index].price;
		bag->curr_weight -= items->item[index].weight;
	}
}

void	signal_handler_parent(int signum, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;

	if (signum == SIGUSR1)
	{
		write(1, "Update childs bag\n", 19);
		signalize_all(SIGUSR1);
	}
}

void	signal_handler_child(int signum, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;

	if (signum == SIGUSR1)
		printf("batata\n");
	else if (signum == SIGUSR2)
		printf("cebola\n");
	fflush(0);
	exit(0);
}
