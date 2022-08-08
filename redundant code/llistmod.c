#include "shell.h"

//Appending value to the "dirlist" linked list
dirlist *append(dirlist **head, char * dir)
{
	dirlist *n_node = malloc(sizeof(dirlist));
	dirlist *tail;

	if (!n_node)
		return NULL;

	n_node->dir = dir;
	n_node->next = NULL;

	if (*head)
	{
		tail = *head;
		while(tail)
			tail = tail->next;
		tail->next = n_node;
	}
	else
		*head = n_node;

	return n_node;
}

//freeing memory alloted to "dirlist" linked list
void release_dir(dirlist *listhead)
{
	dirlist *next;

	while(listhead)
	{
		next = listhead->next;
		free(listhead->dir);
		free(listhead);

		listhead = next;
	}
}
