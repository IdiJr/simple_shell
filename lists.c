#include "shell.h"

/**
 * add_sep_node_end - adds a separator at the end
 * of a seplist.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
seplist *add_sep_node_end(seplist **head, char sep)
{
	seplist *new, *temp;

	new = malloc(sizeof(seplist));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sep_list(seplist **head)
{
	seplist *temp;
	seplist *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - adds command line at the end
 * of  linelist.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
linelist *add_line_node_end(linelist **head, char *line)
{
	linelist *new, *temp;

	new = malloc(sizeof(linelist));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_line_list - frees a linelist
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(linelist **head)
{
	linelist *temp;
	linelist *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
