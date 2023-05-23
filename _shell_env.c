#include "shell.h"

/**
 * sh_myenv - current env
 * @inf: potential arguments structure
 * Return: 0 - Always
 */
int sh_myenv(info_t *inf)
{
	print_ls_str(inf->sh_env);
	return (0);
}

/**
 * _shellgetenv - gets the env variable
 * @inf: potential arguments structure
 * @envname: environment variable name
 * Return: the value
 */

char *_shellgetenv(info_t *inf, const char *envname)
{
	list_t *nd = inf->sh_env;
	char *q;

	while (nd)
	{
		q = sh_starts_with(nd->str, envname);
		if (q && *q)
			return (q);
		nd = nd->next;
	}
	return (NULL);
}


/**
 * sh_myunsetenv - Remove an environment variable
 * @inf: potential arguments structure
 * Return: 0
 */

int sh_myunsetenv(info_t *inf)
{
	int j;

	if (inf->sh_arg_cnt == 1)
	{
		_shell_eputs("Not enough arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->sh_arg_cnt; j++)
		sh_unsetenv(inf, inf->argv[j]);

	return (0);
}

/**
 * sh_populate_env_list - populates env linked list
 * @inf: potential arguments structure
 * Return: Always 0
 */
int sh_populate_env_list(info_t *inf)
{
	list_t *nd = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		sh_add_node_end(&nd, environ[j], 0);
	inf->sh_env = nd;
	return (0);
}

/**
 * sh_mysetenv - Initialize new env variable or modify an existing one
 * @inf: potential arguments structure
 * Return: 0
 */

int sh_mysetenv(info_t *inf)
{
	if (inf->sh_arg_cnt != 3)
	{
		_shell_eputs("Wrong qty of arguments\n");
		return (1);
	}
	if (sh_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

