#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @buf: address of buffer
 * @inf: parameter struct
 * @len: address of len var
 *
 * Return: bytes
 */
ssize_t input_buf(inf_x *inf, char **buf, size_t *len)
{
ssize_t q = 0;
size_t len_p = 0;
if (!*len)
{
free(*buf);
*buf = NULL;
signal(SIGINT, sigintHandler);
#if USE_GETLINE
q = getline(buf, &len_p, stdin);
#else
q = _getline(info, buf, &len_p);
#endif
if (q > 0)
{
if ((*buf)[q - 1] == '\n')
{
(*buf)[q - 1] = '\0';
q--;
}
inf->linecount_flag = 1;
remove_comments(*buf);
build_histor_list(inf, *buf, inf->histcount++);
{
*len = q;
inf->cmd_buf = buf;
}
}
}
return (q);
}

/**
 * get_input - gets a line minus the newline
 * @inf: parameter struct
 *
 * Return: bytes
 */
ssize_t get_input(inf_x *inf)
{
static char *buf;
static size_t a, t, len;
ssize_t q = 0;
char **buf_n = &(inf->arg), *n;
_putchar(BUF_FLUSH);
q = input_buf(inf, &buf, &len);
if (q == -1)
return (-1);
if (len)
{
t = a;
n = buf + a;
check_chain(inf, buf, &t, a, len);
while (t < len)
{
if (is_chain(inf, buf, &t))
break;
t++;
}
a = t + 1;
if (a >= len)
{
a = len = 0;
inf->cmd_buf_type = CMD_NORM;
}
*buf_n = n;
return (_strlen(n));
}
*buf_n = buf;
return (q);
}

/**
 * read_buf - reads a buffer
 * @a: size
 * @inf: parameter struct
 * @buf: buffer
 *
 * Return: q
 */
ssize_t read_buf(inf_x *inf, char *buf, size_t *a)
{
ssize_t q = 0;
if (*a)
return (0);
q = read(inf->readfd, buf, READ_BUF_SIZE);
if (q >= 0)
*a = q;
return (q);
}

/**
 * _getline - gets the next line of input
 * @pnt: address of pointer to buffer
 * @inf: parameter struct
 * @length: size of preallocated ptr buffer
 *
 * Return: c
 */
int _getline(inf_x *inf, char **pnt, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t a, len;
size_t d;
ssize_t q = 0, c = 0;
char *n = NULL, *new_n = NULL, *s;
n = *pnt;
if (n && length)
c = *length;
if (a == len)
a = len = 0;
q = read_buf(inf, buf, &len);
if (q == -1 || (q == 0 && len == 0))
return (-1);
s = _strchr(buf + a, '\n');
d = s ? 1 + (unsigned int)(s - buf) : len;
new_n = _realloc(n, c, c ? c + d : d + 1);
if (!new_n)
return (n ? free(n), -1 : -1);
if (c)
_strncat(new_n, buf + a, d - a);
else
_strncpy(new_n, buf + a, d - a + 1);
c += d - a;
a = d;
n = new_n;
if (length)
*length = c;
*pnt = n;
return (c);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
