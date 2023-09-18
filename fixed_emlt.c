#include "shell.h"

/**
 * _shellexit - exits the shell
 * @inf: Structure pertaining potential arguments
 *
 * Return: exits with a given exit status
 */
int _shellexit(inf_x *inf)
{
int exitcheck;
if (inf->argv[1])
{
exitcheck = _erratoi(inf->argv[1]);
if (exitcheck == -1)
{
inf->status = 2;
print_error(inf, "Illegal number: ");
_eputs(inf->argv[1]);
_eputchar('\n');
return (1);
}
inf->err_numb = _erratoi(inf->argv[1]);
return (-2);
}
inf->err_numb = -1;
return (-2);
}

/**
 * _shellcd - changes the current directory of the process
 * @inf: Structure pertaining potential arguments
 *
 *  Return: 0
 */
int _shellcd(inf_x *inf)
{
char *a, *direct, buffer[1024];
int chdir_ret;
a = getcwd(buffer, 1024);
if (!a)
_puts("TODO: >>getcwd failure emsg here<<\n");
if (!inf->argv[1])
{
direct = _getenv(inf, "HOME=");
if (!direct)
chdir_ret = /* TODO: what should this be? */
chdir((direct = _getenv(inf, "PWD=")) ? direct : "/");
else
chdir_ret = chdir(direct);
}
else if (_strcmp(inf->argv[1], "-") == 0)
{
if (!_getenv(inf, "OLDPWD="))
{
_puts(a);
_putchar('\n');
return (1);
}
_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
chdir_ret = /* TODO: what should this be? */
chdir((direct = _getenv(inf, "OLDPWD=")) ? direct : "/");
}
else
chdir_ret = chdir(inf->argv[1]);
if (chdir_ret == -1)
{
print_error(inf, "can't cd to ");
_eputs(inf->argv[1]), _eputchar('\n');
}
else
{
_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
_setenv(inf, "PWD", getcwd(buffer, 1024));
}
return (0);
}

/**
 * _shellhelp - changes the current directory
 * @inf: Structure pertaining potential arguments
 *
 * Return: 0
 */
int _shellhelp(inf_x *inf)
{
char **arg_array;
arg_array = inf->argv;
_puts("help call works. Function not yet implemented \n");
if (0)
_puts(*arg_array);
return (0);
}
