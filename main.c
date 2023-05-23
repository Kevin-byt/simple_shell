#include "shell.h"

/**
 * main - code  point of entry
 * @arg_cnt: number of arguments
 * @arg_vec: vector of arguments
 * Return: 0 - success, otherwise - 1
 */

int main(int arg_cnt, char **arg_vec)
{
	info_t info[] = { INFO_INIT };
	int f_des = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (f_des)
			: "r" (f_des));

	if (arg_cnt == 2)
	{
		f_des = open(arg_vec[1], O_RDONLY);
		if (f_des == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_shell_eputs(arg_vec[0]);
				_shell_eputs(": 0: Can't open ");
				_shell_eputs(arg_vec[1]);
				_shellputchar('\n');
				_shellputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->sh_read_filedes = f_des;
	}
	sh_populate_env_list(info);
	shell_rd_history(info);
	hsh_main_loop(info, arg_vec);
	return (EXIT_SUCCESS);
}


