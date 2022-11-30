#include "proj.h"
#include "struct.h"
#include "utils.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void	base(char **args, bool boost);
void	get_args_info(char **args, bool boost);
void	get_file_info(char *path, pt_items *items, pt_bag *bag);
void	manage_file_info(pt_items *items, pt_bag *bag, char *buffer);
int		process_string_add_item(pt_items items, char *str);
void	error_handler(int error_code, pt_items items, pt_bag bag);

pt_info	info = NULL;

int main(int argc, char **argv)
{
	if (argc == 2 && (strcmp("-h", argv[1]) == 0 || strcmp("--help", argv[1]) == 0))
	{
		printf("Usage: ./proj [OPTION] order_number path/file number_of_processes program_runtime\n");
		printf("\t-h, --help\t\tdisplay this help and exit\n");
		printf("\t-b, --boost\t\ttriggers the boost option at the runtime\n");
		exit(0);
	}
	else if (argc == 6)
	{
		if (strcmp("-b", argv[1]) == 0|| strcmp("--boost", argv[1]) == 0)
			base(&argv[2], true);
		error_handler(1, NULL, NULL);
	}
	else if (argc == 5)
		base(&argv[1], false);
	error_handler(1, NULL, NULL);
}

void	base(char **args, bool boost)
{
	pt_items	items;
	pt_bag		bag;

	items = 0;
	bag = 0;
	get_args_info(args, boost);
	get_file_info(info->file_name, &items, &bag);
	proj(info, items, bag);
	free(items);
	free(info);
	free(bag);
	exit(0);

/* 	printf("num_order=%d \tfile=%s \tnum_processes=%d \ttime_limit=%d \tbest_result=%d \tnum_items=%d\n", 
		info->num_order, info->file_name, info->num_processes, info->time_limit, info->best_result, info->num_items);
	for (int i = 0; i < info->num_items; i++)
		printf("%d ", bag->items[i]);
	printf("\nmax_weight=%d\tcurr_weight=%d\tcurr_price=%d\n", bag->max_weight, bag->curr_weight, bag->curr_price);
	for (int i = 0; i < info->num_items; i++)
		printf("item[%d] \tprice=%d \tweight=%d\n", i, items->item[i].price, items->item[i].weight);
 */
}

void	get_args_info(char **args, bool boost)
{
	if (atoi(args[0]) < 0 || atoi(args[2]) <= 0 || atoi(args[3]) <= 0 || !strstr(args[1], ".txt"))
		error_handler(1, NULL, NULL);
	info = __init_info(atoi(args[0]), args[1], atoi(args[2]), atoi(args[3]), boost);
	if (!info)
		error_handler(2, NULL, NULL);
}

void	get_file_info(char *path, pt_items *items, pt_bag *bag)
{
	FILE *	stream;
	char	buffer[1024];

	if (!(stream = fopen(path, "r")))
		error_handler(3, *items, *bag);
	while (fgets(buffer, 1024, stream))
		manage_file_info(items, bag, buffer);
	info->num_items = (*items)->size;
	fclose(stream);
}

void	manage_file_info(pt_items *items, pt_bag *bag, char *buffer)
{
	static int	counter = 0;

	if (counter == 0)
	{
		info->num_items = atoi(buffer);
		if (!(*items = __init_items(info->num_items)))
			error_handler(2, *items, *bag);
	}
	else if (counter == 1)
	{
		if (!(*bag = __init_bag(atoi(buffer), info->num_items))) 
			error_handler(2, *items, *bag);
	}
	else
	{
		if (info->num_items-- <= 0)
			(info->best_result < atoi(buffer)) ? info->best_result = atoi(buffer) : 0 ;
		else
		{
			if (process_string_add_item(*items, buffer))
				error_handler(4, *items, *bag);
		}
	}
	counter++;
}

int	process_string_add_item(pt_items items, char *str)
{
	char **	temp;

	temp = ft_split(str, ' ');
	if (!temp || !temp[0] || !temp[1])
		return (1);
	__add_item(items, atoi(temp[0]), atoi(temp[1]));
	free(temp[1]);
	free(temp[0]);
	free(temp);
	return (0);
}

void	error_handler(int error_code, pt_items items, pt_bag bag)
{
	if (error_code == 1)
		printf("Invalid arguments!\n");
	else if (error_code == 2)
		printf("Crash while initializing framework!\n");
	else if (error_code == 3)
		printf("Crash while opening the file!\n");
	else if (error_code == 4)
		printf("Crash while processing the file!\n");
	else if (error_code == 5)
		printf("Invalid arguments!\n");

	free(items);
	free(bag);
	free(info);

	exit(0);
}
