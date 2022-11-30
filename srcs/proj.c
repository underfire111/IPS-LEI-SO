#include "proj.h"

#include <fcntl.h>
#include <memory.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void	set_shared_memory(pt_bag bag, pt_bag *result, t_stats **stats);
void	kill_all();
void	update_all(int signum);
void	signal_handler_parent(int signum);
void	signal_handler_child(int signum);
void	generate_results_0(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats);
void	generate_results_1(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats);
void	update_bag_status_0(pt_items items, pt_bag bag, int index);
void	update_bag_status_1(pt_items items, pt_bag bag, int index);
double	calc_time_in_secs(struct timeval t1, struct timeval t2);


typedef struct	sigaction sigaction_t;

pt_info	_info = 0;
int		cheat = 0;

void	proj_0(pt_info temp, pt_items items, pt_bag bag)
{
	t_stats *	stats;
	sem_t *		update;
	pt_bag		result;

	_info = temp;
	sem_unlink("update");
	update = sem_open("update", O_CREAT, 0644, 1);
	set_shared_memory(bag, &result, &stats);
	for (int i = 0; i < _info->num_processes; i++)
	{
		_info->cpids[i] = fork();
		if (_info->cpids[i] == 0)
			generate_results_0(items, bag, result, update, stats);
	}

	sleep(_info->time_limit);
	kill_all();
	sem_close(update);
	
	printf("| %4d | %4d | %7d | %6d | %6d | %9ld  | %2.8f |\n",
		_info->num_order, _info->time_limit, _info->num_processes,
		_info->best_result, result->curr_price, stats->iterator,
		calc_time_in_secs(stats->time, stats->begin));

}

void	proj_1(pt_info temp, pt_items items, pt_bag bag)
{
	t_stats *	stats;
	sem_t *		update;
	pt_bag		result;

	_info = temp;
	sem_unlink("update");
	update = sem_open("update", O_CREAT, 0644, 0);
	set_shared_memory(bag, &result, &stats);
	for (int i = 0; i < _info->num_processes; i++)
	{
		_info->cpids[i] = fork();
		if (_info->cpids[i] == 0)
		{
			sigaction_t	sa = { 0 };
	
			sa.sa_flags = 0;
			sa.sa_handler = signal_handler_child;
			sigaction(SIGUSR1, &sa, NULL);
			sigaction(SIGUSR2, &sa, NULL);

			sem_post(update);

			pause();

			generate_results_1(items, bag, result, update, stats);
		}
	}

	sigaction_t	sa = { 0 };
	
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler_parent;
	sigaction(SIGUSR1, &sa, NULL);

	for (int i = 0; i < _info->num_processes; i++)
		sem_wait(update);
	sem_post(update);

	update_all(SIGUSR1);

	struct timeval t;

	do
	{
		gettimeofday(&t, NULL);
	} while (calc_time_in_secs(t, stats->begin) <= (double)_info->time_limit);
	
	kill_all();
	
	sem_close(update);
	
		printf("| %4d | %4d | %7d | %6d | %6d | %9ld  | %2.9f |\n",
		_info->num_order, _info->time_limit, _info->num_processes,
		_info->best_result, result->curr_price, stats->iterator,
		calc_time_in_secs(stats->time, stats->begin));

}

void	set_shared_memory(pt_bag bag, pt_bag *result, t_stats **stats)
{
	char *	keys;

	keys = (char *)mmap(NULL, sizeof(char) * _info->num_items + 1, PROT_READ |
		PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	memset(keys, 0, _info->num_items);
	(*result) = (pt_bag)mmap(NULL, sizeof(struct s_bag), PROT_READ |
		PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	(*(*result)) = *bag;
	(*(*result)).items = keys;
	(*stats) = (t_stats *)mmap(NULL, sizeof(t_stats), PROT_READ |
			PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	(*(*stats)) = __init_stats();
}

void	kill_all()
{
	int	status;

	for (int i = 0; i < _info->num_processes; i++)
	{
		kill(_info->cpids[i], SIGKILL);
		wait(&status);
	}
	free(_info->cpids);
}

void	update_all(int signum)
{
	for (int i = 0; i < _info->num_processes; i++)
		kill(_info->cpids[i], signum);
}

void	unnamed_function(pt_bag b1, pt_bag b2)
{
	b1->curr_price = b2->curr_price;
	b1->curr_weight = b2->curr_weight;
	memcpy(b1->items, b2->items, _info->num_items);
}

void	generate_results_0(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats)
{
	size_t		iterator;
	int			r_index;
	
	srand(getpid() + time(NULL));
	iterator = 0;

	while (++iterator)
	{
		r_index = rand() % items->size;
		update_bag_status_0(items, bag, r_index);
		if (bag->curr_weight > bag->max_weight * 2)
			update_bag_status_0(items, bag, r_index);
		sem_wait(update);
		if (bag->curr_price > result->curr_price && bag->curr_weight <= bag->max_weight)
		{
			unnamed_function(result, bag);
			stats->iterator = iterator;
			gettimeofday(&stats->time, NULL);
		}
		sem_post(update);
	}
}

void	generate_results_1(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats)
{
	size_t		iterator;
	int			reset;
	int			r_index;
	
	reset = 0;
	iterator = 0;
	srand(getpid() + time(NULL));
	while (++iterator && ++reset)
	{
		if (cheat-- == 1 || reset == 100)
		{
			sem_wait(update);
			unnamed_function(bag, result);
			sem_post(update);
			reset = 0;
		}
		r_index = rand() % items->size;
		update_bag_status_1(items, bag, r_index);
		if (bag->curr_price > result->curr_price)
		{
			sem_wait(update);
			if (bag->curr_price > result->curr_price)
			{
				unnamed_function(result, bag);
				stats->iterator = iterator;
				gettimeofday(&stats->time, NULL);
				if (_info->num_processes > 1)
					kill(getppid(), SIGUSR1);
				reset = 0;
			}
			sem_post(update);
		}
	}
}

void	update_bag_status_0(pt_items items, pt_bag bag, int index)
{
	if (bag->items[index] == 0)
	{
		bag->items[index]++;
		bag->curr_price += items->item[index].price;
		bag->curr_weight += items->item[index].weight;
	}
	else
	{
		bag->items[index]--;
		bag->curr_price -= items->item[index].price;
		bag->curr_weight -= items->item[index].weight;
	}
}

void	update_bag_status_1(pt_items items, pt_bag bag, int index)
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

void	signal_handler_parent(int signum)
{
	static long counter = 0;

	if (signum == SIGUSR1 && (++counter % 10) == 0)
		update_all(SIGUSR2);
}

void	signal_handler_child(int signum)
{
	if (signum == SIGUSR1)
		;
	else if (signum == SIGUSR2)
		cheat = 1;
}

double	calc_time_in_secs(struct timeval t1, struct timeval t2)
{
	return ((t1.tv_sec - t2.tv_sec) + (t1.tv_usec - t2.tv_usec) / 1000000.0);
}

