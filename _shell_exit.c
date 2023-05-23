#include "shell.h"

/**
 **_shell_strch - searches character in string
 *@a: parsed string
 *@b: searched character
 *Return: memory area pointer
 */

char *_shell_strch(char *a, char b)
{
	do {
		if (*a == b)
			return (a);
	} while (*a++ != '\0');

	return (NULL);
}

/**
 **_shell_strncat - joins two strings
 *@dt: string 1
 *@sc: string 2
 *@m: No. of bytes
 *Return: concatenated string
 */
char *_shell_strncat(char *dt, char *sc, int m)
{
	int x;
	int y;
	char *c = dt;

	x = 0;
	y = 0;
	while (dt[x] != '\0')
		x++;
	while (sc[y] != '\0' && y < m)
	{
		dt[x] = sc[y];
		x++;
		y++;
	}
	if (y < m)
		dt[x] = '\0';
	return (c);
}

/**
 **_shell_strncpy - copy string
 *@dt: copy destination
 *@sc: copy source
 *@m: No. of characters copied
 *Return: concatenated string
 */

char *_shell_strncpy(char *dt, char *sc, int m)
{
	int y;
	int z;
	char *c = dt;

	y = 0;
	while (sc[y] != '\0' && y < m - 1)
	{
		dt[y] = sc[y];
		y++;
	}
	if (y < m)
	{
		z = y;
		while (z < m)
		{
			dt[z] = '\0';
			z++;
		}
	}
	return (c);
}

