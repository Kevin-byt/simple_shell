#include "shell.h"

/**
 * _shellputfd - writes the character s to given file descriptor
 * @s: printed character
 * @file_des: filedescriptor
 * Return: 1 on success, -1 on err
 */

int _shellputfd(char s, int file_des)
{
	static int x;
	static char bf[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(file_des, bf, x);
		x = 0;
	}
	if (s != BUF_FLUSH)
		bf[x++] = s;
	return (1);
}

/**
 * _shellputchar - writes character s to standard err
 * @s: printed character
 * Return: 1 - success, -1 on error
 */

int _shellputchar(char s)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (s != BUF_FLUSH)
		buf[x++] = s;
	return (1);
}

/**
 * _shell_eputs - input string print
 * @st: printed string
 * Return: void
 */
void _shell_eputs(char *st)
{
	int x = 0;

	if (!st)
		return;
	while (st[x] != '\0')
	{
		_shellputchar(st[x]);
		x++;
	}
}

/**
 * _shellputsfd - prints an input string
 * @st: printed string
 * @file_des: filedescriptor
 * Return: the number of chars put
 */

int _shellputsfd(char *st, int file_des)
{
	int x = 0;

	if (!st)
		return (0);
	while (*st)
	{
		x += _shellputfd(*st++, file_des);
	}
	return (x);
}


