#include "shell.h"

/**
 * bfree_ptr - ptr free and NULL address
 * @pr: pointer address to free
 * Return: 1 success, otherwise 0.
 */

int bfree_ptr(void **pr)
{
	if (pr && *pr)
	{
		free(*pr);
		*pr = NULL;
		return (1);
	}
	return (0);
}


