#include "shell.h"

/**
 * hsh_main_loop - shell main loop
 * @inf: struct for params and return
 * @arg_vec: argument vector from main()
 * Return: 0 - success, 1 - error, or error code
 */

int hsh_main_loop(info_t *inf, char **arg_vec)
{
	ssize_t a = 0;
	int ret_val = 0;

	while (a != -1 && ret_val != -2)
	{
		_shell_clear_info(inf);
		if (is_interactive(inf))
			_shell_puts("$ ");
		_shellputchar(BUF_FLUSH);
		a = shell_get_input(inf);
		if (a != -1)
		{
			_shell_set_inf(inf, arg_vec);
			ret_val = sh_get_builtin_cmd(inf);
			if (ret_val == -1)
				sh_find_cmd_path(inf);
		}
		else if (is_interactive(inf))
			_shell_putchar('\n');
		_shell_free_inf(inf, 0);
	}
	shell_wr_history(inf);
	_shell_free_inf(inf, 1);
	if (!is_interactive(inf) && inf->last_cmd_status)
		exit(inf->last_cmd_status);
	if (ret_val == -2)
	{
		if (inf->sh_error_code == -1)
			exit(inf->last_cmd_status);
		exit(inf->sh_error_code);
	}
	return (ret_val);
}

/**
 * sh_find_cmd_path - gets a command in PATH
 * @inf: struct for params and return
 * Return: void
 */

void sh_find_cmd_path(info_t *inf)
{
	char *cmdpath = NULL;
	int x, y;

	inf->sh_str_path = inf->argv[0];
	if (inf->sh_linecnt_flag == 1)
	{
		inf->sh_line_cnt++;
		inf->sh_linecnt_flag = 0;
	}
	for (x = 0, y = 0; inf->arg[x]; x++)
		if (!is_delimiter(inf->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	cmdpath = sh_find_path_cmd(inf, _shellgetenv(inf, "PATH="), inf->argv[0]);
	if (cmdpath)
	{
		inf->sh_str_path = cmdpath;
		sh_fork_exec_cmd(inf);
	}
	else
	{
		if ((is_interactive(inf) || _shellgetenv(inf, "PATH=")
					|| inf->argv[0][0] == '/') && check_file_cmd(inf, inf->argv[0]))
			sh_fork_exec_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->last_cmd_status = 127;
			error_print(inf, "not found\n");
		}
	}
}

/**
 * sh_get_builtin_cmd - looks for a builtin command
 * @inf: struct for params and return
 * Return: -1 - builtin not found,
 * 0 - Success,
 * 1 - builtin found but not successful,
 * 2 - builtin signals exit()
 */

int sh_get_builtin_cmd(info_t *inf)
{
	int x, ret_built_in = -1;
	builtin_table builtin_table[] = {
		{"exit", sh_exit},
		{"sh_env", sh_myenv},
		{"help", _help},
		{"sh_hist_node", _hist},
		{"setenv", sh_mysetenv},
		{"unsetenv", sh_myunsetenv},
		{"cd", _cd},
		{"sh_alias_node", _alias},
		{NULL, NULL}
	};

	for (x = 0; builtin_table[x].type; x++)
		if (sh_strcmp(inf->argv[0], builtin_table[x].type) == 0)
		{
			inf->sh_line_cnt++;
			ret_built_in = builtin_table[x].func(inf);
			break;
		}
	return (ret_built_in);
}

/**
 * sh_fork_exec_cmd - forks a an exec thread to run cmd
 * @inf: struct for params and return
 * Return: void
 */

void sh_fork_exec_cmd(info_t *inf)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(inf->sh_str_path, inf->argv, _shell_get_environ(inf)) == -1)
		{
			_shell_free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->last_cmd_status));
		if (WIFEXITED(inf->last_cmd_status))
		{
			inf->last_cmd_status = WEXITSTATUS(inf->last_cmd_status);
			if (inf->last_cmd_status == 126)
				error_print(inf, "Permission denied\n");
		}
	}
}

