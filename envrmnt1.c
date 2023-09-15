#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @inf: Structure containing potential arguments
 *
 * Return: Always 0
 */
char **get_environ(inf_x *inf)
{
if (!inf->environ || inf->env_changed)
{
inf->environ = list_to_strings(inf->env);
inf->env_changed = 0;
}
return (inf->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @inf: Structure containing potential arguments
 * @var: the string env var property
 *
 *  Return: 1 on delete
 */
int _unsetenv(inf_x *inf, char *var)
{
list_x *node = inf->env;
size_t a = 0;
char *n;
if (!node || !var)
return (0);
while (node)
{
n = starts_with(node->string, var);
if (n && *n == '=')
{
inf->env_changed = delete_node_at_index(&(inf->env), a);
a = 0;
node = inf->env;
continue;
}
node = node->nxt;
a++;
}
return (inf->env_changed);
}

/**
 * _setenv - Initialize a new environment variable
 * @inf: Structure containing potential arguments
 * @var: the string env var property
 * @value: the string env var value
 *
 *  Return: Always 0
 */
int _setenv(inf_x *inf, char *var, char *value)
{
char *buf = NULL;
list_x *node;
char *n;
if (!var || !value)
return (0);
buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = inf->env;
while (node)
{
n = starts_with(node->string, var);
if (n && *n == '=')
{
free(node->string);
node->string = buf;
inf->env_changed = 1;
return (0);
}
node = node->nxt;
}
add_node_end(&(inf->env), buf, 0);
free(buf);
inf->env_changed = 1;
return (0);
}
