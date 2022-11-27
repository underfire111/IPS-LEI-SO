#if !defined(STRUCT_H)
# define STRUCT_H

# include <stdlib.h>

typedef struct s_bag *pt_bag;
typedef struct s_item *pt_item;
typedef struct s_items *pt_items;
typedef struct s_info *pt_info;

struct s_bag
{
	int *	items;
	int		max_weight;
	int 	curr_weight;
	int		curr_price;
};

struct s_item
{
	int	price;
	int weight;
};

struct s_items
{
	pt_item	item;
	size_t	size;
};

struct s_info
{
	int		num_order;
	char *	file_name;
	int 	num_processes;
	int		time_limit;
	int		num_items;
	int		best_result;
};

pt_bag		__init_bag(int max_weight, int num_items);

pt_items	__init_items(size_t capacity);

void 		__add_item(pt_items items, int price, int weight);

pt_info		__init_info(int num_order, char *file_name, int num_processes, int time_limit);

#endif // STRUCT_H
