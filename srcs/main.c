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
void	print_help();

pt_info	info = NULL;

/**
 * The main function analize the arguments and adopt a behaviour according to.
 * 
 * @param [int] number of arguments.
 * @param [char **] arguments.
*/
int main(int argc, char **argv)
{
	if (argc == 2 && (strcmp("-h", argv[1]) == 0 || strcmp("--help", argv[1]) == 0))
	{
		print_help();
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

/**
 * That function is the base of the project. It declares the structures, initialize them, calls out
 * for the function that applies the algorithm, frees the memory allocated to the structures and exit
 * the program.
 * 
 *  @param [char **] argurments.
 * 	@param [bool] status of flag boost.
*/
void	base(char **args, bool boost)
{
	pt_items	items;
	pt_bag		bag;

	items = 0;
	bag = 0;
	get_args_info(args, boost);
	get_file_info(info->file_name, &items, &bag);
	if (info->boost)
		proj_1(info, items, bag);
	else
		proj_0(info, items, bag);
	free(items->item);
	free(bag->items);
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

/**
 * That function process the arguments and initialize the structure s_info.
 * 
 * @param [char **] arguments.
 * @param [bool] status of boost.
*/
void	get_args_info(char **args, bool boost)
{
	if (atoi(args[0]) < 0 || atoi(args[2]) <= 0 || atoi(args[3]) <= 0 || !strstr(args[1], ".txt"))
		error_handler(1, NULL, NULL);
	info = __init_info(atoi(args[0]), args[1], atoi(args[2]), atoi(args[3]), boost);
	if (!info)
		error_handler(2, NULL, NULL);
}

/**
 * That function reads the file and call out the functions responsible for proccessing its informations.
 * 
 *  @param [char *] string of character with the file path.
 *  @param [pt_items *] reference to the pointer of structure s_items.
 *  @param [pt_bag *] reference to the pointer of structure s_bag.
*/
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

/**
 * That function process the string of character get by parameter and treats it according
 * with the current counter value. In general it gets the information out of the file
 * and imports it into the atributes.
 * 
 *  @param [pt_items *] reference to the pointer of structure s_items.
 *  @param [pt_bag *] reference to the pointer of structure s_bag.
 *  @param [char *] string of character read from file.
*/
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

/**
 * That function process a string passed by parameter. If it have all the requirements needed
 * it creates a new item with the status get through the string and add it to the array of
 * items into the structure s_items.
 * 
 *  @param [pt_items] pointer to the structure s_items.
 *  @param [char *] string of characters to be processed.
 * 
 *  @return 0 - if it adds successfuly the item to the array.
 *  @return 1 - if it fails to add the item to the array.
*/
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

/**
 * That function prints out the manual of the program.
*/
void	print_help()
{
	printf("Usage: ./prog [OPTION] order_number path/file number_of_processes program_runtime\n");
	printf("\t-h, --help\t\tdisplay this help and exit\n");
	printf("\t-b, --boost\t\ttriggers the boost option at the runtime\n");
}

/**
 * That function prints out an error message acording the the error code, frees the the memory
 * allocated to the structures s_info, s_items and s_bag and terminate the process.
 * 
 *  @param [int] error code.
 *  @param [pt_items] pointer to structure s_items.
 *  @param [pt_bag] pointer to structure s_bag.
*/
void	error_handler(int error_code, pt_items items, pt_bag bag)
{
	if (error_code == 1)
	{
		printf("Invalid arguments!\n\n");
		print_help();
	}
	else if (error_code == 2)
		printf("Crash while initializing framework!\n");
	else if (error_code == 3)
		printf("Crash while opening the file!\n");
	else if (error_code == 4)
		printf("Crash while processing the file!\n");
	else if (error_code == 5)
		printf("Invalid arguments!\n");

	if (bag != NULL)
		free(bag->items);
	if (items != NULL)
		free(items->item);
	free(items);
	free(bag);
	free(info);

	exit(0);
}
