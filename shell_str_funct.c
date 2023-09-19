#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @c: considered string to check
 *
 * Return: integer length of string
 */
int _strlen(char *c)
{
int a = 0;
if (!c)
return (0);
while (c++)
a++;
return (a);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: (-) if str1 < str2, (+) if str1 > str2, 0 if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
while (*str1 && *str2)
{
if (*str1 != *str2)
return (*str1 - *str2);
str1++;
str2++;
}
if (*str1 == *str2)
return (0);
else
return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if pin starts with haypile
 * @hypile: considered string to search
 * @pin: substring to find
 *
 * Return: address of next char of haypile
 */
char *starts_with(const char *hypile, const char *pin)
{
while (*pin)
if (*pin++ != *hypile++)
return (NULL);
return ((char *)hypile);
}

/**
 * _strcat - concatenates two strings
 * @dst: destination buffer
 * @srce: source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dst, char *srce)
{
char *ret = dst;
while (*dst)
dst++;
while (*srce)
*dst++ = *srce++;
*dst = *srce;
return (ret);
}
