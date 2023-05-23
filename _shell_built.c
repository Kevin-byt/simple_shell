#include "shell.h"

/**
 * reset_alias - sets alias
 * @inf: struct parameter
 * @st: alias of string
 * Return: 0 - success, 1 - error
 */

int reset_alias(info_t *inf, char *st)
{
	char *q;
	char ch;
	int result;

	q = _shell_strch(st, '=');
	if (!q)
		return (1);
	ch = *q;
	*q = 0;
	result = index_delete_node(&(inf->sh_alias_node),
		_index_node(inf->sh_alias_node,
		node_start_pref(inf->sh_alias_node, st, -1)));
	*q = ch;
	return (result);
}

/**
 * _hist - displays history list
 * @inf: potential arguments structure.
 *  Return: 0 - Always
 */
int _hist(info_t *inf)
{
	sh_ls_print(inf->sh_hist_node);
	return (0);
}

/**
 * alias_print - prints the alias string
 * @nd: alias node *
 * Return: 0 - success, 1 - error
 */

int alias_print(list_t *nd)
{
	char *q = NULL;
	char *d = NULL;

	if (nd)
	{
		q = _shell_strch(nd->str, '=');
		for (d = nd->str; d <= q; d++)
		{
			_shell_putchar(*d);
			_shell_putchar('\'');
			_shell_puts(q + 1);
			_shell_puts("'\n");
		}
		return (0);
	}
	return (1);
}


/**
 * alias_set - sets alias to string
 * @inf: parameter struct
 * @st: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int alias_set(info_t *inf, char *st)
{
	char *q;

	q = _shell_strch(st, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (reset_alias(inf, st));

	reset_alias(inf, st);
	return (sh_add_node_end(&(inf->sh_alias_node), st, 0) == NULL);
}

/**
 *_alias - like the builtin fn alias (man alias)
 * @inf:  potential arguments structure.
 * Return: 0 - Always
 */

int _alias(info_t *inf)
{
	int x = 0;
	char *q = NULL;
	list_t *nd = NULL;

	if (inf->sh_arg_cnt == 1)
	{
		nd = inf->sh_alias_node;
		while (nd)
		{
			alias_print(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (x = 1; inf->argv[x]; x++)
	{
		q = _shell_strch(inf->argv[x], '=');
		if (q)
			alias_set(inf, inf->argv[x]);
		else
			alias_print(node_start_pref(inf->sh_alias_node, inf->argv[x], '='));
	}

	return (0);
}
