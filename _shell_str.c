#include "shell.h"

/**
 * sh_starts_with - checks string start
 * @s: string
 * @str_part: part to search in string
 * Return: NULL or next char address
 */

char *sh_starts_with(const char *s, const char *str_part)
{
	while (*str_part)
		if (*str_part++ != *s++)
			return (NULL);
	return ((char *)s);
}

/**
 * sh_strlen - gets the string length
 * @str: the string
 * Return: string length
 */

int sh_strlen(char *str)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str++)
		x++;
	return (x);
}

/**
 * sh_strcat - joins 2 strings
 * @destination: destination
 * @source: source
 * Return: destination buffer pointer
 */

char *sh_strcat(char *destination, char *source)
{
	char *destptr = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (destptr);
}

/**
 * sh_strcmp - compares 2 strings lexicogarphically.
 * @str_1: string 1
 * @str_2: string 2
 * Return:  positive - str_1 > str_2,
 * negative - str_1 < str_2,
 * zero - str_1 == str_2
 */

int sh_strcmp(char *str_1, char *str_2)
{
	while (*str_1 && *str_2)
	{
		if (*str_1 != *str_2)
			return (*str_1 - *str_2);
		str_1++;
		str_2++;
	}
	if (*str_1 == *str_2)
		return (0);
	else
		return (*str_1 < *str_2 ? -1 : 1);
}

