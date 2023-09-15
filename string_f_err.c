#include "shell.h"

/**
 *_eputs - prints an input string
 * @string: considered string
 *
 * Return: Nothing
 */
void _eputs(char *string)
{
int a = 0;
if (!string)
return;
while (string[a] != '\0')
{
_eputchar(string[a]);
a++;
}
}

/**
 * _eputchar - writes the character c to stderr
 * @s: The character to print
 *
 * Return: 1 on success
 */
int _eputchar(char s)
{
static int a;
static char buf[WRITE_BUF_SIZE];
if (s == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(2, buf, a);
a = 0;
}
if (s != BUF_FLUSH)
buf[a++] = s;
return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @fd: The filedescriptor
 * @c: considered character to print
 *
 * Return: 1 on success
 */
int _putfd(char c, int fd)
{
static int a;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
{
write(fd, buf, a);
a = 0;
}
if (c != BUF_FLUSH)
buf[a++] = c;
return (1);
}

/**
 *_putsfd - prints an input string
 * @fd: the filedescriptor
 * @string: considered string
 *
 * Return: chars put
 */
int _putsfd(char *string, int fd)
{
int a = 0;
if (!string)
return (0);
while (*string)
{
a += _putfd(*string++, fd);
}
return (a);
}
