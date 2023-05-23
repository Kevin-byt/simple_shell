#include "shell.h"

/**
 * **sh_str_to_words2 - split string to words
 * @str: string
 * @delimiter: delimeter
 * Return: array of strings pointer, otherwise NULL
 */

char **sh_str_to_words2(char *str, char delimiter)
{
	int w, x, y = 0;
	int z, wordcount = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (w = 0; str[w] != '\0'; w++)
		if ((str[w] != delimiter && str[w + 1] == delimiter) ||
				    (str[w] != delimiter && !str[w + 1]) || str[w + 1] == delimiter)
			wordcount++;
	if (wordcount == 0)
		return (NULL);
	s = malloc((1 + wordcount) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < wordcount; x++)
	{
		while (str[w] == delimiter && str[w] != delimiter)
			w++;
		y = 0;
		while (str[w + y] != delimiter && str[w + y] && str[w + y] != delimiter)
			y++;
		s[x] = malloc((y + 1) * sizeof(char));
		if (!s[x])
		{
			for (y = 0; y < x; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}

/**
 * **sh_str_to_words - splits string to words ignoring repeat delimiters
 * @str: string
 * @e: delimeter
 * Return: array of strings pointer, otherwise NULL
 */

char **sh_str_to_words(char *str, char *e)
{
	char **s;
	int w, x, y = 0;
	int z, wordcount = 0;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!e)
		e = " ";
	for (w = 0; str[w] != '\0'; w++)
		if (!is_delimiter(str[w], e) && (is_delimiter(str[w + 1], e) || !str[w + 1]))
			wordcount++;

	if (wordcount == 0)
		return (NULL);
	s = malloc((1 + wordcount) * sizeof(char *));
	if (!s)
		return (NULL);
	for (w = 0, x = 0; x < wordcount; x++)
	{
		while (is_delimiter(str[w], e))
			w++;
		y = 0;
		while (!is_delimiter(str[w + y], e) && str[w + y])
			y++;
		s[x] = malloc((y + 1) * sizeof(char));
		if (!s[x])
		{
			for (y = 0; y < x; y++)
				free(s[y]);
			free(s);
			return (NULL);
		}
		for (z = 0; z < y; z++)
			s[x][z] = str[w++];
		s[x][z] = 0;
	}
	s[x] = NULL;
	return (s);
}

