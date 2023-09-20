#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments
 *
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
info->environ = list_to_strings(info->env);
info->env_changed = 0;
}
return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments
 * @var: the string env var property
 *
 *  Return: 1 on delete
 */
int _unsetenv(info_t *info, char *var)
{
list_x *node = info->env;
size_t a = 0;
char *n;
if (!node || !var)
return (0);
while (node)
{
n = starts_with(node->string, var);
if (n && *n == '=')
{
info->env_changed = remov_node_at_index(&(info->env), a);
a = 0;
node = info->env;
continue;
}
node = node->nxt;
a++;
}
return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable
 * @info: Structure containing potential arguments
 * @var: the string env var property
 * @value: the string env var value
 *
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
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
node = info->env;
while (node)
{
n = starts_with(node->string, var);
if (n && *n == '=')
{
free(node->string);
node->string = buf;
info->env_changed = 1;
return (0);
}
node = node->nxt;
}
add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
