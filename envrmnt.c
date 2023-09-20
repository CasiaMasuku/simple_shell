#include "shell.h"

/**
 * _shellenv - prints the current environment
 * @info: Structure consisting potential arguments
 *
 * Return: Always 0
 */
int _shellenv(info_t *info)
{
print_list_str(info->env);
return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure consisting potential arguments
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
list_x *node = info->env;
char *a;
while (node)
{
a = starts_with(node->string, name);
if (a && *a)
return (a);
node = node->nxt;
}
return (NULL);
}

/**
 * _shellsetenv - Initializes a new environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: 0
 */
int _shellsetenv(info_t *info)
{
if (info->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(info, info->argv[1], info->argv[2]))
return (0);
return (1);
}

/**
 * _shellunsetenv - Removes an environment variable
 * @info: Structure consisting potential arguments
 *
 * Return: 0
 */
int _shellunsetenv(info_t *info)
{
int n;
if (info->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (n = 1; n <= info->argc; n++)
_unsetenv(info, info->argv[n]);
return (0);
}

/**
 * fill_env_list - fills env linked list
 * @info: Structure pertaining potential arguments
 *
 * Return: 0
 */
int fill_env_list(info_t *info)
{
list_x *node = NULL;
size_t a;
for (a = 0; environ[a]; a++)
add_node_end(&node, environ[a], 0);
info->env = node;
return (0);
}
