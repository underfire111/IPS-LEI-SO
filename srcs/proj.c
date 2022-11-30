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
void	kill_all();
void	update_all(int signum);
void	signal_handler_parent(int signum);
void	signal_handler_child(int signum);
void	generate_results(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats);
void	update_bag_status(pt_items items, pt_bag bag, int index);

typedef struct	sigaction sigaction_t;

pt_info	_info = 0;
int		cheat = 0;

void	proj(pt_info temp, pt_items items, pt_bag bag)
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
			sigaction_t	sa;
	
			sa.sa_flags = 0;
			sa.sa_handler = signal_handler_child;
			sigaction(SIGUSR1, &sa, NULL);
			sigaction(SIGUSR2, &sa, NULL);

			sem_post(update);

			pause();

			generate_results(items, bag, result, update, stats);

		}
	}

	sigaction_t	sa;
	
	sa.sa_flags = 0;
	sa.sa_handler = signal_handler_parent;
	sigaction(SIGUSR1, &sa, NULL);

	for (int i = 0; i < _info->num_processes; i++)
		sem_wait(update);
	sem_post(update);

	update_all(SIGUSR1);
	
	while ((time(NULL) - stats->begin) <= _info->time_limit) ;
	
	kill_all();
	
	sem_close(update);
	
	printf("| %4d | %4d | %7d | %6d | %6d | %9ld  | %11ld |\n",
		_info->num_order, _info->time_limit, _info->num_processes,
		_info->best_result, result->curr_price, stats->iterator,
		(stats->time - stats->begin));

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
	for (int i = 0; i < _info->num_items; i++)
		b1->items[i] = b2->items[i];
}

void	generate_results(pt_items items, pt_bag bag, pt_bag result, sem_t *update, t_stats *stats)
{
	size_t		iterator;
	int			reset;
	int			r_index;
	
	srand(getpid() + time(NULL));
	iterator = 0;
	reset = 0;
	while (++iterator && ++reset)
	{
		if (cheat-- == 1 || reset == 100)
		{
			unnamed_function(bag, result);
			reset = 0;
		}
		r_index = rand() % items->size;
		update_bag_status(items, bag, r_index);
		sem_wait(update);
		if (bag->curr_price > result->curr_price)
		{
			unnamed_function(result, bag);
			stats->iterator = iterator;
			stats->time = time(NULL);
			if (_info->boost && _info->num_processes > 1)
				kill(getppid(), SIGUSR1);
			reset = 0;
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
