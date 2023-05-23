#include "shell.h"

/**
 * _strtoi - changes string to an integer
 * @c: converted string
 * Return: 0, otherwise -1 on error
 */

int _strtoi(char *c)
{
	int x = 0;
	unsigned long int res = 0;

	if (*c == '+')
		c++;
	for (x = 0;  c[x] != '\0'; x++)
	{
		if (c[x] >= '0' && c[x] <= '9')
		{
			res *= 10;
			res += (c[x] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * rm_comments - function replaces first instance of '#' with '\0'
 * @buffer: string address
 * Return: 0;
 */

void rm_comments(char *buffer)
{
	int x;

	for (x = 0; buffer[x] != '\0'; x++)
		if (buffer[x] == '#' && (!x || buffer[x - 1] == ' '))
		{
			buffer[x] = '\0';
			break;
		}
}

/**
 * print_decimal - prints integer number (base 10)
 * @inp: input
 * @write_file: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int inp, int write_file)
{
	int (*__putchar)(char) = _shell_putchar;
	int i;
	int cnt = 0;
	unsigned int _abs_;
	unsigned int crrnt;

	if (write_file == STDERR_FILENO)
		__putchar = _shellputchar;
	if (inp < 0)
	{
		_abs_ = -inp;
		__putchar('-');
		cnt++;
	}
	else
		_abs_ = inp;
	crrnt = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + crrnt / i);
			cnt++;
		}
		crrnt %= i;
	}
	__putchar('0' + crrnt);
	cnt++;

	return (cnt);
}

/**
 * cnvt_number - converter function, a clone of itoa
 * @number: number
 * @num_base: base
 * @set_flag: argument flags
 * Return: string
 */
char *cnvt_number(long int number, int num_base, int set_flag)
{
	static char *arr;
	static char buff[50];
	char sgn = 0;
	char *sh_ptr;
	unsigned long d = number;

	if (!(set_flag & CONVERT_UNSIGNED) && number < 0)
	{
		d = -number;
		sgn = '-';

	}
	arr = set_flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	sh_ptr = &buff[49];
	*sh_ptr = '\0';

	do	{
		*--sh_ptr = arr[d % num_base];
		d /= num_base;
	} while (d != 0);

	if (sgn)
		*--sh_ptr = sgn;
	return (sh_ptr);
}

/**
 * error_print - prints an error message
 * @inf: the parameter & return info struct
 * @errstr: specified error type
 * Return: 0 otherwise -1 on error
 */

void error_print(info_t *inf, char *errstr)
{
	_shell_eputs(inf->sh_prog_filename);
	_shell_eputs(": ");
	print_decimal(inf->sh_line_cnt, STDERR_FILENO);
	_shell_eputs(": ");
	_shell_eputs(inf->argv[0]);
	_shell_eputs(": ");
	_shell_eputs(errstr);
}
