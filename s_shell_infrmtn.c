#include "shell.h"

/**
 * clear_info - initializes inf_x struct
 * @inf: struct address
 */
void clear_info(inf_x *inf)
{
inf->arg = NULL;
inf->argv = NULL;
inf->path = NULL;
inf->argc = 0;
}

/**
 * set_info - initializes inf_x struct
 * @inf: struct address
 * @av: argument vector
 */
void set_info(inf_x *inf, char **av)
{
int a = 0;
inf->f.name = av[0];
if (inf->arg)
{
inf->argv = strtow(inf->arg, " \t");
if (!inf->argv)
{
inf->argv = malloc(sizeof(char *) * 2);
if (inf->argv)
{
inf->argv[0] = _strdup(inf->arg);
inf->argv[1] = NULL;
}
}
for (a = 0; inf->argv && inf->argv[a]; a++)
;
inf->argc = a;
replace_alias(inf);
replace_vars(inf);
}
}

/**
 * free_info - frees inf_x struct fields
 * @inf: struct address
 * @all: true if freeing all fields
 */
void free_info(inf_x *inf, int all)
{
ffree(inf->argv);
inf->argv = NULL;
inf->path = NULL;
if (all)
{
if (!inf->cmd_buf)
free(inf->arg);
if (inf->env)
free_list(&(inf->env));
if (inf->hist)
free_list(&(inf->hist));
if (inf->alias)
free_list(&(inf->alias));
ffree(inf->environ);
inf->environ = NULL;
bfree((void **)inf->cmd_buf);
if (inf->readfd > 2)
close(inf->readfd);
_putchar(BUF_FLUSH);
}
}
