#include "shell.h"

/**
 * sh_exit - function to exit the shell
 * @inf: potential arguments structure.
 * Return: given exit status. 0 - if inf.argv[0] != "exit"
 */

int sh_exit(info_t *inf)
{
	int checkexit;

	if (inf->argv[1]) /* If there is an exit arguement */
	{
		checkexit = _strtoi(inf->argv[1]);
		if (checkexit == -1)
		{
			inf->last_cmd_status = 2;
			error_print(inf, "Illegal number: ");
			_shell_eputs(inf->argv[1]);
			_shellputchar('\n');
			return (1);
		}
		inf->sh_error_code = _strtoi(inf->argv[1]);
		return (-2);
	}
	inf->sh_error_code = -1;
	return (-2);
}

/**
 * _cd - change process directory
 * @inf: potential arguments structure
 * Return: 0
 */

int _cd(info_t *inf)
{
	char *c;
	char *folder;
	char buff[1024];
	int fold_ret;

	c = getcwd(buff, 1024);
	if (!c)
		_shell_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		folder = _shellgetenv(inf, "HOME=");
		if (!folder)
			fold_ret = chdir((folder = _shellgetenv(inf, "PWD=")) ? folder : "/");
		else
			fold_ret = chdir(folder);
	}
	else if (sh_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_shellgetenv(inf, "OLDPWD="))
		{
			_shell_puts(c);
			_shell_putchar('\n');
			return (1);
		}
		_shell_puts(_shellgetenv(inf, "OLDPWD=")), _shell_putchar('\n');
		fold_ret = chdir((folder = _shellgetenv(inf, "OLDPWD=")) ? folder : "/");
	}
	else
		fold_ret = chdir(inf->argv[1]);
	if (fold_ret == -1)
	{
		error_print(inf, "can't cd to ");
		_shell_eputs(inf->argv[1]), _shellputchar('\n');
	}
	else
	{
		sh_setenv(inf, "OLDPWD", _shellgetenv(inf, "PWD="));
		sh_setenv(inf, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _help - changes the current directory of the process
 * @inf: potential arguments structure
 * Return: 0 - Always
 */

int _help(info_t *inf)
{
	char **arg_array;

	arg_array = inf->argv;
	_shell_puts("help call works. Function not yet implemented \n");
	if (0)
		_shell_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

