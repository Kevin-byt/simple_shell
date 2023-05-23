#include "shell.h"

/**
 * list_to_str_array -  list->str list array
 * @node_head: first node pointer
 * Return: string array
 */

char **list_to_str_array(list_t *node_head)
{
	list_t *nd = node_head;
	size_t i = shell_lst_ln(node_head), k;
	char *str_ptr;
	char **strs;

	if (!node_head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; nd; nd = nd->next, i++)
	{
		str_ptr = malloc(sh_strlen(nd->str) + 1);
		if (!str_ptr)
		{
			for (k = 0; k < i; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str_ptr = _shell_strcpy(str_ptr, nd->str);
		strs[i] = str_ptr;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * shell_lst_ln -gets the length of a linked list
 * @node_head: first node
 * Return: list size
 */

size_t shell_lst_ln(const list_t *node_head)
{
	size_t x = 0;

	while (node_head)
	{
		node_head = node_head->next;
		x++;
	}
	return (x);
}

/**
 * _index_node - gets node index
 * @node_head: list head pointer
 * @nd: node pointer
 * Return: node index on success,  otherwise -1
 */

ssize_t _index_node(list_t *node_head, list_t *nd)
{
	size_t x = 0;

	while (node_head)
	{
		if (node_head == nd)
			return (x);
		node_head = node_head->next;
		x++;
	}
	return (-1);
}

/**
 * node_start_pref - gets node with prefix start
 * @nd: list head pointer
 * @node_pref: matching string
 * @s: character after prefix to match
 * Return: Matched node - SUCCESS, else NULL
 */

list_t *node_start_pref(list_t *nd, char *node_pref, char s)
{
	char *q = NULL;

	while (nd)
	{
		q = sh_starts_with(nd->str, node_pref);
		if (q && ((s == -1) || (*q == s)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * sh_ls_print - gets all list_t linked list elements
 * @head_node: first node pointer
 * Return: list size
 */

size_t sh_ls_print(const list_t *head_node)
{
	size_t x = 0;

	while (head_node)
	{
		_shell_puts(cnvt_number(head_node->num, 10, 0));
		_shell_putchar(':');
		_shell_putchar(' ');
		_shell_puts(head_node->str ? head_node->str : "(nil)");
		_shell_puts("\n");
		head_node = head_node->next;
		x++;
	}
	return (x);
}
