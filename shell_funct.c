#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode
 */
int interactive(info_t *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @s: considerd char to check
 * @gov: delimeter string
 *
 * Return: 1 if true
 */
int is_delim(char s, char *gov)
{
while (*gov)
if (*gov++ == s)
return (1);
return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @s: The character to input
 *
 * Return: 1 if s is alphabetic
 */
int _isalpha(int s)
{
if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
return (1);
else
return (0);
}

/**
 * _atoi - converts a string to an integer
 * @c: the string to be converted
 *
 * Return: 0 if no numbers in string
 */
int _atoi(char *c)
{
int a, sign = 1, flag = 0, output;
unsigned int outcome = 0;
for (a = 0;  c[a] != '\0' && flag != 2; a++)
{
if (c[a] == '-')
sign *= -1;
if (c[a] >= '0' && c[a] <= '9')
{
flag = 1;
outcome *= 10;
outcome += (c[a] - '0');
}
else if (flag == 1)
flag = 2;
}
if (sign == -1)
output = -outcome;
else
output = outcome;
return (output);
}
