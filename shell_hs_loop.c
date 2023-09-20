#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main
 *
 * Return: 0 on success
 */
int hsh(info_t *info, char **av)
{
ssize_t q = 0;
int builtin_ret = 0;
while (q != -1 && builtin_ret != -2)
{
clear_info(info);
if (interactive(info))
_puts("$ ");
_eputchar(BUF_FLUSH);
q = get_input(info);
if (q != -1)
{
set_info(info, av);
builtin_ret = find_builtin(info);
if (builtin_ret == -1)
find_cmd(info);
}
else if (interactive(info))
_putchar('\n');
free_info(info, 0);
}
write_hist(info);
free_info(info, 1);
if (!interactive(info) && info->status)
exit(info->status);
if (builtin_ret == -2)
{
if (info->err_numb == -1)
exit(info->status);
exit(info->err_numb);
}
return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found
 */
int find_builtin(info_t *info)
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
for (a = 0; builtintbl[a].kind; a++)
if (_strcmp(info->argv[0], builtintbl[a].kind) == 0)
{
info->line_count++;
built_in_ret = builtintbl[a].functn(info);
break;
}
return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
char *path = NULL;
int a, d;
info->path = info->argv[0];
if (info->linecount_flag == 1)
{
info->line_count++;
info->linecount_flag = 0;
}
for (a = 0, d = 0; info->arg[a]; a++)
if (!is_delim(info->arg[a], " \t\n"))
d++;
if (!d)
return;
path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
if (path)
{
info->path = path;
fork_cmd(info);
}
else
{
if ((interactive(info) || _getenv(info, "PATH=")
|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
fork_cmd(info);
else if (*(info->arg) != '\n')
{
info->status = 127;
print_error(info, "not found\n");
}
}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
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
if (execve(info->path, info->argv, get_environ(info)) == -1)
{
free_info(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
print_error(info, "Permission denied\n");
}
}
}
