#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data)
{
	t_list *node = mx_create_node(data);
	node->next = NULL;
	if (*list == NULL) {
		*list = node;
		return;
	}
	t_list* list_p = *list;
	while (list_p->next) {
		list_p = list_p->next;
	}
	list_p->next = node;
}
