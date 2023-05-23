#include "shell.h"

/**
 * _shell_putchar - writes character to stdout
 * @ch: character
 * Return: 1 - On success, -1 - error
 */

int _shell_putchar(char ch)
{
	static int x;
	static char buffe[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(1, buffe, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buffe[x++] = ch;
	return (1);
}

/**
 * _shell_strcpy - string copy
 * @destination: destination
 * @source: source
 * Return: destination pointer
 */

char *_shell_strcpy(char *destination, char *source)
{
	int x = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[x])
	{
		destination[x] = source[x];
		x++;
	}
	destination[x] = 0;
	return (destination);
}

/**
 * _shell_puts - input string
 * @s: printed string
 * Return: void
 */

void _shell_puts(char *s)
{
	int x = 0;

	if (!s)
		return;
	while (s[x] != '\0')
	{
		_shell_putchar(s[x]);
		x++;
	}
}

/**
 * _shell_strdup - string duplicate
 * @s: string
 * Return: duplicated string pointer
 */

char *_shell_strdup(const char *s)
{
	int lng = 0;
	char *dup_str;

	if (s == NULL)
		return (NULL);
	while (*s++)
		lng++;
	dup_str = malloc(sizeof(char) * (lng + 1));
	if (!dup_str)
		return (NULL);
	for (lng++; lng--;)
		dup_str[lng] = *--s;
	return (dup_str);
}

