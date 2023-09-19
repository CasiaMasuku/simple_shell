#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @inf: info struct
 * @path: path to the file
 *
 * Return: 1 if true
 */
int is_cmd(inf_x *inf, char *path)
{
struct stat st;
(void)inf;
if (!path || stat(path, &st))
return (0);
if (st.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
 * dup_chars - duplicates characters
 * @pthstring: the PATH string
 * @begin: beggining index
 * @end: ending index
 *
 * Return: pointer
 */
char *dup_chars(char *pthstring, int begin, int end)
{
static char buf[1024];
int a = 0, d = 0;
for (d = 0, a = begin; a < end; a++)
if (pthstring[a] != ':')
buf[d++] = pthstring[a];
buf[d] = 0;
return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @inf: info struct
 * @cmd: the cmd to find
 * @pthstring: the PATH string
 *
 * Return: full path of cmd
 */
char *find_path(inf_x *inf, char *pthstring, char *cmd)
{
int a = 0, curr_pos = 0;
char *path;
if (!pthstring)
return (NULL);
if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
{
if (is_cmd(inf, cmd))
return (cmd);
}
while (1)
{
if (!pthstring[a] || pthstring[a] == ':')
{
path = dup_chars(pthstring, curr_pos, a);
if (!*path)
_strcat(path, cmd);
else
{
_strcat(path, "/");
_strcat(path, cmd);
}
if (is_cmd(inf, path))
return (path);
if (!pthstring[a])
break;
curr_pos = a;
}
a++;
}
return (NULL);
}
