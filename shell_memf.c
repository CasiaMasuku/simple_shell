#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@c: pointer to the memory area
 *@d: byte to fill *c
 *@n: capacity of bytes to be filled
 *
 *Return: (c)
 */
char *_memset(char *c, char d, unsigned int n)
{
unsigned int a;
for (a = 0; a < n; a++)
c[a] = d;
return (c);
}

/**
 * ffree - frees a string of strings
 * @f: string of strings
 */
void ffree(char **f)
{
char **i = f;
if (!f)
return;
while (*f)
free(*f++);
free(i);
}

/**
 * _realloc - reallocates a block of memory
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * @pnt: pointer
 *
 * Return: pointer
 */
void *_realloc(void *pnt, unsigned int old_size, unsigned int new_size)
{
char *n;
if (!pnt)
return (malloc(new_size));
if (!new_size)
return (free(pnt), NULL);
if (new_size == old_size)
return (pnt);
n = malloc(new_size);
if (!n)
return (NULL);
old_size = old_size < new_size ? old_size : new_size;
while (old_size--)
n[old_size] = ((char *)pnt)[old_size];
free(pnt);
return (n);
}
