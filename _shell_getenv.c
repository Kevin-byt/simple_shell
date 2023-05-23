#include "shell.h"

/**
 * _shell_get_environ - string array of our environ
 * @inf: potential arguments structure
 * Return: 0 - always
 */

char **_shell_get_environ(info_t *inf)
{
	if (!inf->sh_environ_cpy || inf->sh_env_changed_flag)
	{
		inf->sh_environ_cpy = list_to_str_array(inf->sh_env);
		inf->sh_env_changed_flag = 0;
	}

	return (inf->sh_environ_cpy);
}

/**
 * sh_setenv - new or modify env variable
 * @inf: potential arguments structure
 * @variable: var property
 * @val: var value
 *  Return: 0 - Always
 */

int sh_setenv(info_t *inf, char *variable, char *val)
{
	char *buff = NULL;
	list_t *nd;
	char *q;

	if (!variable || !val)
		return (0);

	buff = malloc(sh_strlen(variable) + sh_strlen(val) + 2);
	if (!buff)
		return (1);
	_shell_strcpy(buff, variable);
	sh_strcat(buff, "=");
	sh_strcat(buff, val);
	nd = inf->sh_env;
	while (nd)
	{
		q = sh_starts_with(nd->str, variable);
		if (q && *q == '=')
		{
			free(nd->str);
			nd->str = buff;
			inf->sh_env_changed_flag = 1;
			return (0);
		}
		nd = nd->next;
	}
	sh_add_node_end(&(inf->sh_env), buff, 0);
	free(buff);
	inf->sh_env_changed_flag = 1;
	return (0);
}

/**
 * sh_unsetenv - Removes environment variable
 * @inf: potential arguments structure
 * @vr: the string env var property
 * Return: 1 on delete, 0 otherwise
 */

int sh_unsetenv(info_t *inf, char *vr)
{
	list_t *nd = inf->sh_env;
	size_t x = 0;
	char *q;

	if (!nd || !vr)
		return (0);

	while (nd)
	{
		q = sh_starts_with(nd->str, vr);
		if (q && *q == '=')
		{
			inf->sh_env_changed_flag = index_delete_node(&(inf->sh_env), x);
			x = 0;
			nd = inf->sh_env;
			continue;
		}
		nd = nd->next;
		x++;
	}
	return (inf->sh_env_changed_flag);
}
