#include "shell.h"

/**
 * ffree_str - frees string of strings
 * @str_strings: string
 */

void ffree_str(char **str_strings)
{
	char **z = str_strings;

	if (!str_strings)
		return;
	while (*str_strings)
		free(*str_strings++);
	free(z);
}

/**
 * sh_mem_realloc - reallocates memory block
 * @pre_block_ptr: previous block ptr
 * @old_block_sz: previous block byte size
 * @new_block_sz: new block byte size
 * Return: old block name pointer.
 */
void *sh_mem_realloc(void *pre_block_ptr, unsigned int old_block_sz,
	unsigned int new_block_sz)
{
	char *q;

	if (!pre_block_ptr)
		return (malloc(new_block_sz));
	if (!new_block_sz)
		return (free(pre_block_ptr), NULL);
	if (new_block_sz == old_block_sz)
		return (pre_block_ptr);

	q = malloc(new_block_sz);
	if (!q)
		return (NULL);

	old_block_sz = old_block_sz < new_block_sz ? old_block_sz : new_block_sz;
	while (old_block_sz--)
		q[old_block_sz] = ((char *)pre_block_ptr)[old_block_sz];
	free(pre_block_ptr);
	return (q);
}

/**
 * _shell_memset - fill memory
 * @sh_mem: memory area pointer
 * @mem_byte: the byte to fill the memory with
 * @byte_num: number of bytes to fill the memory
 * Return: pointer to memory area
 */

char *_shell_memset(char *sh_mem, char mem_byte, unsigned int byte_num)
{
	unsigned int x;

	for (x = 0; x < byte_num; x++)
		sh_mem[x] = mem_byte;
	return (sh_mem);
}

