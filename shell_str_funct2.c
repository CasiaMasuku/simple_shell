#include "shell.h"

/**
 * *_strncpy - copies a string
 * @dst:  destination string to be copied to
 * @srce: source string
 * @p: characters to be copied
 *
 * Return: the concatenated string
 */
char *_strncpy(char *dst, char *srce, int p)
{
int a, d;
char *c = dst;
a = 0;
while (srce[a] != '\0' && a < p - 1)
{
dst[a] = srce[a];
a++;
}
if (a < p)
{
d = a;
while (d < p)
{
dst[d] = '\0';
d++;
}
}
return (c);
}

/**
 * *_strncat - concatenates two strings
 * @dst: first string
 * @srce: second string
 * @p: bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *_strncat(char *dst, char *srce, int p)
{
int a, d;
char *c = dst;
a = 0;
d = 0;
while (dst[a] != '\0')
a++;
while (srce[d] != '\0' && d < p)
{
dst[a] = srce[d];
a++;
d++;
}
if (d < p)
dst[a] = '\0';
return (c);
}

/**
 * *_strchr - locates a character in a string
 * @c: considered string to be parsed
 * @s: character to look for
 *
 * Return: (c) a pointer to the memory area s
 */
char *_strchr(char *c, char s)
{
do {
if (*c == s)
return (c);
} while (*c++ != '\0');
return (NULL);
}
