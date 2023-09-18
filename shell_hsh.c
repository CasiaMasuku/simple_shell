#include "shell.h"

/**
 * hsh - main shell loop
 * @inf: the parameter & return info struct
 * @av: the argument vector from main
 *
 * Return: 0 on success
 */
int hsh(inf_x *inf, char **av)
{
ssize_t q = 0;
int builtin_ret = 0;
while (q != -1 && builtin_ret != -2)
{
clear_info(inf);
if (interactive(inf))
_puts("$ ");
_eputchar(BUF_FLUSH);
q = get_input(inf);
if (q != -1)
{
set_info(inf, av);
builtin_ret = find_builtin(inf);
if (builtin_ret == -1)
find_cmd(inf);
}
else if (interactive(inf))
_putchar('\n');
free_info(inf, 0);
}
write_hist(inf);
free_info(inf, 1);
if (!interactive(inf) && inf->status)
exit(inf->status);
if (builtin_ret == -2)
{
if (inf->err_num == -1)
exit(inf->status);
exit(inf->err_num);
}
return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @inf: the parameter & return info struct
 *
 * Return: -1 if builtin not found
 */
int find_builtin(inf_x *inf)
{
int a, built_in_ret = -1;
builtin_table builtintbl[] = {
{"exit", _shellexit},
{"env", _shellenv},
{"help", _shellhelp},
{"history", _shellhist},
{"setenv", _shellsetenv},
{"unsetenv", _shellunsetenv},
{"cd", _shellcd},
{"alias", _shellalias},
{NULL, NULL}
};
for (a = 0; builtintbl[a].type; a++)
if (_strcmp(inf->argv[0], builtintbl[a].type) == 0)
{
inf->line_count++;
built_in_ret = builtintbl[a].func(inf);
break;
}
return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(inf_x *inf)
{
char *path = NULL;
int a, d;
inf->path = inf->argv[0];
if (inf->linecount_flag == 1)
{
inf->line_count++;
inf->linecount_flag = 0;
}
for (a = 0, d = 0; inf->arg[a]; a++)
if (!is_delim(inf->arg[a], " \t\n"))
d++;
if (!d)
return;
path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
if (path)
{
inf->path = path;
fork_cmd(inf);
}
else
{
if ((interactive(inf) || _getenv(inf, "PATH=")
|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
fork_cmd(inf);
else if (*(inf->arg) != '\n')
{
inf->status = 127;
print_error(inf, "not found\n");
}
}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @inf: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(inf_x *inf)
{
pid_t child_pid;
child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
{
free_inf(inf, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(inf->status));
if (WIFEXITED(inf->status))
{
inf->status = WEXITSTATUS(inf->status);
if (inf->status == 126)
print_error(inf, "Permission denied\n");
}
}
}
