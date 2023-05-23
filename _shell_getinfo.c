#include "shell.h"

/**
 * _shell_set_inf - initializes info_t struct
 * @inf: struct address
 * @arg_vec: argument vector
 */

void _shell_set_inf(info_t *inf, char **arg_vec)
{
	int x = 0;

	inf->sh_prog_filename = arg_vec[0];
	if (inf->arg)
	{
		inf->argv = sh_str_to_words(inf->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _shell_strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (x = 0; inf->argv && inf->argv[x]; x++)
			;
		inf->sh_arg_cnt = x;

		sh_replace_tk_alias(inf);
		sh_replace_tk_vars(inf);
	}
}

/**
 * _shell_clear_info - info_t struct init
 * @inf: address of the struct
 */

void _shell_clear_info(info_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->sh_str_path = NULL;
	inf->sh_arg_cnt = 0;
}

/**
 * _shell_free_inf - frees struct fields
 * @inf: address of the struct
 * @all_structs: True for freeing all structs
 */
void _shell_free_inf(info_t *inf, int all_structs)
{
	ffree_str(inf->argv);
	inf->argv = NULL;
	inf->sh_str_path = NULL;
	if (all_structs)
	{
		if (!inf->cmd_buffer_address)
			free(inf->arg);
		if (inf->sh_env)
			sh_free_list(&(inf->sh_env));
		if (inf->sh_hist_node)
			sh_free_list(&(inf->sh_hist_node));
		if (inf->sh_alias_node)
			sh_free_list(&(inf->sh_alias_node));
		ffree_str(inf->sh_environ_cpy);
			inf->sh_environ_cpy = NULL;
		bfree_ptr((void **)inf->cmd_buffer_address);
		if (inf->sh_read_filedes > 2)
			close(inf->sh_read_filedes);
		_shell_putchar(BUF_FLUSH);
	}
}


