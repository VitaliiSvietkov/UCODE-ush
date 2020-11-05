#include "../inc/libmx.h"

void mx_push_front(t_list **list, void *data) {
	t_list *newNode = mx_create_node(data);
	newNode->next = *list;
	*list = newNode;
}
