#include "shell.h"

/**
 * _isalphabet - checks for alphabetic character
 * @ch: The character to input
 * Return: 1 if alphabetic character, 0 if not
 */

int _isalphabet(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 * is_delimiter - checks if character is a delimeter
 * @ch: the checked character
 * @del: delimeter string
 * Return: 1 if delimiter, 0 otherwise
 */

int is_delimiter(char ch, char *del)
{
	while (*del)
		if (*del++ == ch)
			return (1);
	return (0);
}

/**
 * is_interactive - checks if shell is in the interactive mode
 * @inf: struct address *
 * Return: 1 if true, 0 if false
 */

int is_interactive(info_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->sh_read_filedes <= 2);
}

/**
 * _sh_atoi - changes str to int
 * @c: the string converted to int
 * Return: 0
 */

int _sh_atoi(char *c)
{
	int z;
	int sn = 1;
	int checker = 0;
	int res;
	unsigned int result = 0;

	for (z = 0; c[z] != '\0' && checker != 2; z++)
	{
		if (c[z] == '-')
			sn *= -1;

		if (c[z] >= '0' && c[z] <= '9')
		{
			checker = 1;
			result *= 10;
			result += (c[z] - '0');
		}
		else if (checker == 1)
			checker = 2;
	}

	if (sn == -1)
		res = -result;
	else
		res = result;

	return (res);
}


