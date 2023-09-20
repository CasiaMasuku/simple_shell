#include "shell.h"

/**
 * _shellexit - exits the shell
 * @info: Structure pertaining potential arguments
 *
 * Return: exits with a given exit status
 */
int _shellexit(info_t *info)
{
int exitcheck;
if (info->argv[1])
{
exitcheck = _erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
print_error(info, "Illegal number: ");
_eputs(info->argv[1]);
_eputchar('\n');
return (1);
}
info->err_numb = _erratoi(info->argv[1]);
return (-2);
}
info->err_numb = -1;
return (-2);
}

/**
 * _shellcd - changes the current directory of the process
 * @info: Structure pertaining potential arguments
 *
 *  Return: 0
 */
int _shellcd(info_t *info)
{
char *a, *direct, buffer[1024];
int chdir_ret;
a = getcwd(buffer, 1024);
if (!a)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!info->argv[1])
{
direct = _getenv(info, "HOME=");
if (!direct)
chdir_ret = /* TODO: what should this be? */
chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
else
chdir_ret = chdir(direct);
}
else if (_strcmp(info->argv[1], "-") == 0)
{
if (!_getenv(info, "OLDPWD="))
{
_puts(a);
_putchar('\n');
return (1);
}
_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
}
else
chdir_ret = chdir(info->argv[1]);
if (chdir_ret == -1)
{
print_error(info, "can't cd to ");
_eputs(info->argv[1]), _eputchar('\n');
}
else
{
_setenv(info, "OLDPWD", _getenv(info, "PWD="));
_setenv(info, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _shellhelp - changes the current directory
 * @info: Structure pertaining potential arguments
 *
 * Return: 0
 */
int _shellhelp(info_t *info)
{
char **arg_array;
arg_array = info->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
