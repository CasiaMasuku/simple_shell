#include "shell.h"

/**
 * bfree - frees a pointer
 * @pnt: address of the pointer to free
 *
 * Return: 1 if freed
 */
int bfree(void **pnt)
{
if (pnt && *pnt)
{
free(*pnt);
*pnt = NULL;
return (1);
}
return (0);
}
