#include "shell.h"

/**
 * _strcpy - copies a string
 * @dst: the destination
 * @srce: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dst, char *srce)
{
int a = 0;
if (dst == srce || srce == 0)
return (dst);
while (srce[a])
{
dst[a] = srce[a];
a++;
}
dst[a] = 0;
return (dst);
}

/**
 * _strdup - duplicates a string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
int length = 0;
char *ret;
if (string == NULL)
return (NULL);
while (*string++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--string;
return (ret);
}

/**
 *_puts - prints an input string
 *@string: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *string)
{
int a = 0;
if (!string)
return;
while (string[a] != '\0')
{
_putchar(string[a]);
a++;
}
}

/**
 * _putchar - writes the character c to stdout
 * @s: The character to print
 *
 * Return: On success 1.
 */
int _putchar(char s)
{
static int a;
static char buf[WRITE_BUF_SIZE];
if (s == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(1, buf, a);
a = 0;
}
if (s != BUF_FLUSH)
buf[a++] = s;
return (1);
}
