#include "struct.h"

#include <stdlib.h>

typedef struct s_bag t_bag;
typedef struct s_item t_item;
typedef struct s_items t_items;
typedef struct s_info t_info;

pt_bag __init_bag(int max_weight, int num_items)
{
	pt_bag	bag;

	bag = (pt_bag)malloc(sizeof(t_bag));
	if (!bag)
		return (NULL);
	bag->max_weight = max_weight;
	bag->curr_weight = 0;
	bag->curr_price = 0;
	bag->items = (int *)calloc(sizeof(int), num_items);
	if (!bag->items)
	{
		free(bag);
		return (NULL);
	}
	return (bag);
}

void __add_item(pt_items items, int price, int weight)
{
	items->item[items->size].price = price;
	items->item[items->size].weight= weight;
	items->size++;
}

pt_items __init_items(size_t capacity)
{
	pt_items items;

	items = (pt_items)malloc(sizeof(t_items));
	if (!items)
		return (NULL);
	items->item = (pt_item)calloc(sizeof(t_item), capacity);
	if (!items->item)
	{
		free(items);
		return (NULL);
	}
	items->size = 0;
	return (items);
}

pt_info	__init_info(int num_order, char *file_name, int num_processes, int time_limit)
{
	pt_info info;

	info = (pt_info)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->num_order = num_order;
	info->file_name = file_name;
	info->num_processes = num_processes;
	info->time_limit = time_limit;
	info->num_items = 0;
	info->best_result = 0;
	return (info);
}
