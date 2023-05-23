#include "shell.h"

/**
 * sh_chain_check - continue chaining checks on last status
 * @inf: struct of parameter
 * @buffe: character buffer
 * @q: current position in buf address
 * @a: buffer start position
 * @ln: buffer length
 * Return: Nothing
 */

void sh_chain_check(info_t *inf, char *buffe, size_t *q, size_t a, size_t ln)
{
	size_t x = *q;

	if (inf->sh_cmd_buf_type == CMD_AND)
	{
		if (inf->last_cmd_status)
		{
			buffe[a] = 0;
			x = ln;
		}
	}
	if (inf->sh_cmd_buf_type == CMD_OR)
	{
		if (!inf->last_cmd_status)
		{
			buffe[a] = 0;
			x = ln;
		}
	}

	*q = x;
}

/**
 * sh_replace_tk_alias - replaces tokenized string alias
 * @inf: struct of parameter
 * Return: 1 - if replaced, 0 - otherwise
 */

int sh_replace_tk_alias(info_t *inf)
{
	int x;
	list_t *nd;
	char *q;

	for (x = 0; x < 10; x++)
	{
		nd = node_start_pref(inf->sh_alias_node, inf->argv[0], '=');
		if (!nd)
			return (0);
		free(inf->argv[0]);
		q = _shell_strch(nd->str, '=');
		if (!q)
			return (0);
		q = _shell_strdup(q + 1);
		if (!q)
			return (0);
		inf->argv[0] = q;
	}
	return (1);
}

/**
 * sh_string_replace - string replace
 * @old_string: old string address
 * @new_string: new string address
 * Return: 1 - replaced, 0 - otherwise
 */


int sh_string_replace(char **old_string, char *new_string)
{
	free(*old_string);
	*old_string = new_string;
	return (1);
}

/**
 * sh_test_is_chain - tests a chain delimeter
 * @inf: parameter struct
 * @bufe: character buffer
 * @q: current buffer position address
 * Return: 1 - chain delimeter, 0 otherwise
 */

int sh_test_is_chain(info_t *inf, char *bufe, size_t *q)
{
	size_t a = *q;

	if (bufe[a] == '|' && bufe[a + 1] == '|')
	{
		bufe[a] = 0;
		a++;
		inf->sh_cmd_buf_type = CMD_OR;
	}
	else if (bufe[a] == '&' && bufe[a + 1] == '&')
	{
		bufe[a] = 0;
		a++;
		inf->sh_cmd_buf_type = CMD_AND;
	}
	else if (bufe[a] == ';') /* found end of this command */
	{
		bufe[a] = 0; /* replace semicolon with null */
		inf->sh_cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = a;
	return (1);
}

/**
 * sh_replace_tk_vars - replaces tokenized string vars
 * @info: struct
 * Return: 1 - replaced, 0 - otherwise
 */

int sh_replace_tk_vars(info_t *info)
{
	int x = 0;
	list_t *nd;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!sh_strcmp(info->argv[x], "$?"))
		{
			sh_string_replace(&(info->argv[x]),
					_shell_strdup(cnvt_number(info->last_cmd_status, 10, 0)));
			continue;
		}
		if (!sh_strcmp(info->argv[x], "$$"))
		{
			sh_string_replace(&(info->argv[x]),
					_shell_strdup(cnvt_number(getpid(), 10, 0)));
			continue;
		}
		nd = node_start_pref(info->sh_env, &info->argv[x][1], '=');
		if (nd)
		{
			sh_string_replace(&(info->argv[x]),
					_shell_strdup(_shell_strch(nd->str, '=') + 1));
			continue;
		}
		sh_string_replace(&info->argv[x], _shell_strdup(""));

	}
	return (0);
}
