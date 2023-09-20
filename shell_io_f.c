#include "shell.h"

/**
 * get_hist_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_hist_file(info_t *info)
{
char *buf, *direct;
direct = _getenv(info, "HOME=");
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
 * @info: the parameter struct
 *
 * Return: 1 on success
 */
int write_hist(info_t *info)
{
ssize_t fd;
char *filename = get_hist_file(info);
list_x *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->hist; node; node = node->nxt)
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
 * @info: the parameter struct
 *
 * Return: histcount on success
 */
int read_hist(info_t *info)
{
int a, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_hist_file(info);
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
build_hist_list(info, buf + last, linecount++);
last = a + 1;
}
if (last != a)
build_hist_list(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
remov_node_at_index(&(info->hist), 0);
renumber_hist(info);
return (info->histcount);
}

/**
 * build_hist_list - adds entry to a history linked list
 * @linecount: history linecount
 * @info: Structure containing potential arguments
 * @buf: buffer
 *
 * Return: 0
 */
int build_hist_list(info_t *info, char *buf, int linecount)
{
list_x *node = NULL;
if (info->hist)
node = info->hist;
add_node_end(&node, buf, linecount);
if (!info->hist)
info->hist = node;
return (0);
}

/**
 * renumber_hist - renumbers the history linked list
 * @info: Structure containing potential arguments
 *
 * Return: new histcount
 */
int renumber_hist(info_t *info)
{
list_x *node = info->hist;
int a = 0;
while (node)
{
node->numb = a++;
node = node->nxt;
}
return (info->histcount = a);
}
