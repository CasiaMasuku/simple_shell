#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @inf: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(inf_x *inf)
{
char *buf, *direct;
direct = _getenv(info "HOME=");
if (!direct)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(direct) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, direct);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}

/**
 * write_hist - creates a file, or attaches to an existing file
 * @inf: the parameter struct
 *
 * Return: 1 on success
 */
int write_hist(inf_x *inf)
{
ssize_t fd;
char *filename = get_hist_file(inf);
list_x *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = inf->hist; node; node = node->nxt)
{
_putsfd(node->string, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_hist - reads history from file
 * @inf: the parameter struct
 *
 * Return: histcount on success
 */
int read_hist(info_x *inf)
{
int a, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_hist_file(inf);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (a = 0; a < fsize; a++)
if (buf[a] == '\n')
{
buf[a] = 0;
build_hist_list(inf, buf + last, linecount++);
last = a + 1;
}
if (last != a)
build_hist_list(inf, buf + last, linecount++);
free(buf);
inf->histcount = linecount;
while (inf->histcount-- >= HIST_MAX)
delete_node_at_index(&(inf->hist), 0);
renumber_hist(inf);
return (inf->histcount);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @linecount: history linecount
 * @inf: Structure containing potential arguments
 * @buf: buffer
 *
 * Return: 0
 */
int build_hist_list(inf_x *inf, char *buf, int linecount)
{
list_x *node = NULL;
if (inf->hist)
node = inf->hist;
add_node_end(&node, buf, linecount);
if (!inf->hist)
inf->hist = node;
return (0);
}

/**
 * renumber_hist - renumbers the history linked list
 * @inf: Structure containing potential arguments
 *
 * Return: new histcount
 */
int renumber_hist(inf_x *inf)
{
list_x *node = inf->hist;
int a = 0;
while (node)
{
node->numb = a++;
node = node->nxt;
}
return (inf->histcount = i);
}
