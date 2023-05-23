#include "shell.h"

/**
 * sh_find_path_cmd - finds this cmd in the PATH string
 * @inf: struct info
 * @str_path: pathstring
 * @sh_cmd: the command to find
 * Return: cmd path - if found or NULL
 */

char *sh_find_path_cmd(info_t *inf, char *str_path, char *sh_cmd)
{
	int x = 0, index_now = 0;
	char *s_path;

	if (!str_path)
		return (NULL);
	if ((sh_strlen(sh_cmd) > 2) && sh_starts_with(sh_cmd, "./"))
	{
		if (check_file_cmd(inf, sh_cmd))
			return (sh_cmd);
	}
	while (1)
	{
		if (!str_path[x] || str_path[x] == ':')
		{
			s_path = duplicate_characters(str_path, index_now, x);
			if (!*s_path)
				sh_strcat(s_path, sh_cmd);
			else
			{
				sh_strcat(s_path, "/");
				sh_strcat(s_path, sh_cmd);
			}
			if (check_file_cmd(inf, s_path))
				return (s_path);
			if (!str_path[x])
				break;
			index_now = x;
		}
		x++;
	}
	return (NULL);
}

/**
 * check_file_cmd - checks whether a file is executable
 * @inf: struct
 * @file_path: filepath
 * Return: 1 - true, 0 otherwise
 */

int check_file_cmd(info_t *inf, char *file_path)
{
	struct stat fl_st;

	(void)inf;
	if (!file_path || stat(file_path, &fl_st))
		return (0);

	if (fl_st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_characters - duplicates the characters in a string
 * @str_path: the PATH
 * @first_index: first index
 * @last_index: last index
 * Return: new buffer buffer
 */

char *duplicate_characters(char *str_path, int first_index, int last_index)
{
	static char buffe[1024];
	int x = 0, y = 0;

	for (y = 0, x = first_index; x < last_index; x++)
		if (str_path[x] != ':')
			buffe[y++] = str_path[x];
	buffe[y] = 0;
	return (buffe);
}

