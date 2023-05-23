#include "shell.h"

/**
 * sh_add_node_end - adds node at list end
 * @sh_hd: head node address ptr
 * @st: node string field
 * @node_index: index of node
 * Return: list size
 */

list_t *sh_add_node_end(list_t **sh_hd, const char *st, int node_index)
{
	list_t *sh_new_nd, *nd;

	if (!sh_hd)
		return (NULL);

	nd = *sh_hd;
	sh_new_nd = malloc(sizeof(list_t));
	if (!sh_new_nd)
		return (NULL);
	_shell_memset((void *)sh_new_nd, 0, sizeof(list_t));
	sh_new_nd->num = node_index;
	if (st)
	{
		sh_new_nd->str = _shell_strdup(st);
		if (!sh_new_nd->str)
		{
			free(sh_new_nd);
			return (NULL);
		}
	}
	if (nd)
	{
		while (nd->next)
			nd = nd->next;
		nd->next = sh_new_nd;
	}
	else
		*sh_hd = sh_new_nd;
	return (sh_new_nd);
}

/**
 * shell_add_node - adds 1st node
 * @sh_hd: sh_hd node pointer address
 * @sh_str: node
 * @node_index: index of node
 * Return: list size
 */

list_t *shell_add_node(list_t **sh_hd, const char *sh_str, int node_index)
{
	list_t *new_hd;

	if (!sh_hd)
		return (NULL);
	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);
	_shell_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = node_index;
	if (sh_str)
	{
		new_hd->str = _shell_strdup(sh_str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *sh_hd;
	*sh_hd = new_hd;
	return (new_hd);
}

/**
 * print_ls_str - prints str element
 * @first_node: pointer to first node
 * Return: size of list
 */

size_t print_ls_str(const list_t *first_node)
{
	size_t x = 0;

	while (first_node)
	{
		_shell_puts(first_node->str ? first_node->str : "(nil)");
		_shell_puts("\n");
		first_node = first_node->next;
		x++;
	}
	return (x);
}

/**
 * sh_free_list - all list nodes free
 * @head_node_ptr: pointer to head node address
 * Return: void
 */

void sh_free_list(list_t **head_node_ptr)
{
	list_t *nd, *follow_node, *sh_head;

	if (!head_node_ptr || !*head_node_ptr)
		return;
	sh_head = *head_node_ptr;
	nd = sh_head;
	while (nd)
	{
		follow_node = nd->next;
		free(nd->str);
		free(nd);
		nd = follow_node;
	}
	*head_node_ptr = NULL;
}

/**
 * index_delete_node - deletes index node
 * @first_node: first node pointer
 * @node_index: delete node index
 * Return: 1 - success, 0 - failure
 */

int index_delete_node(list_t **first_node, unsigned int node_index)
{
	list_t *nd, *sh_prev_node;
	unsigned int x = 0;

	if (!first_node || !*first_node)
		return (0);

	if (!node_index)
	{
		nd = *first_node;
		*first_node = (*first_node)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *first_node;
	while (nd)
	{
		if (x == node_index)
		{
			sh_prev_node->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		x++;
		sh_prev_node = nd;
		nd = nd->next;
	}
	return (0);
}
