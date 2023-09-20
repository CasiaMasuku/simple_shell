#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @c: considered string to convert
 *
 * Return: 0 if no numbers in string
 */
int _erratoi(char *c)
{
int a = 0;
unsigned long int outcome = 0;
if (*c == '+')
c++;
for (a = 0;  c[a] != '\0'; a++)
{
if (c[a] >= '0' && c[a] <= '9')
{
outcome *= 10;
outcome += (c[a] - '0');
if (outcome > INT_MAX)
return (-1);
}
else
return (-1);
}
return (outcome);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: contains specified error type
 *
 * Return: 0 if no numbers in string
 */
void print_error(info_t *info, char *estr)
{
_eputs(info->f_name);
_eputs(": ");
print_d(info->line_count, STDERR_FILENO);
_eputs(": ");
_eputs(info->argv[0]);
_eputs(": ");
_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: input
 * @fd: filedescriptor
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
int (*__putchar)(char) = _putchar;
int a, count = 0;
unsigned int _abs_, current;
if (fd == STDERR_FILENO)
__putchar = _eputchar;
if (input < 0)
{
_abs_ = -input;
__putchar('-');
count++;
}
else
_abs_ = input;
current = _abs_;
for (a = 1000000000; a > 1; a /= 10)
{
if (_abs_ / a)
{
__putchar('0' + current / a);
count++;
}
current %= a;
}
__putchar('0' + current);
count++;
return (count);
}

/**
 * cnvert_number - converter function, a clone of itoa
 * @flags: argument flags
 * @numb: number
 * @base: base
 *
 * Return: string
 */
char *cnvert_number(long int numb, int base, int flags)
{
static char *array;
static char buffer[50];
char sign = 0;
char *pnt;
unsigned long p = numb;
if (!(flags & CONVERT_UNSIGNED) && numb < 0)
{
p = -numb;
sign = '-';
}
array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
pnt = &buffer[49];
*pnt = '\0';
do {
*--pnt = array[p % base];
p /= base;
} while (p != 0);
if (sign)
*--pnt = sign;
return (pnt);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
int a;
for (a = 0; buf[a] != '\0'; a++)
if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
{
buf[a] = '\0';
break;
}
}
