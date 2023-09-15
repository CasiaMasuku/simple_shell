#include "shell.h"

/**
 * _shellenv - prints the current environment
 * @inf: Structure consisting potential arguments
 *
 * Return: Always 0
 */
int _shellenv(inf_x *inf)
{
print_list_str(inf->env);
return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @inf: Structure consisting potential arguments
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(inf_x *inf, const char *name)
{
list_x *node = inf->env;
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
 * @inf: Structure containing potential arguments. Used to maintain
 *
 * Return: 0
 */
int _shellsetenv(inf_x *inf)
{
if (inf->argc != 3)
{
_eputs("Incorrect number of arguements\n");
return (1);
}
if (_setenv(inf, inf->argv[1], inf->argv[2]))
return (0);
return (1);
}

/**
 * _shellunsetenv - Removes an environment variable
 * @inf: Structure consisting potential arguments
 *
 * Return: 0
 */
int _shellunsetenv(inf_x *inf)
{
int n;
if (inf->argc == 1)
{
_eputs("Too few arguements.\n");
return (1);
}
for (n = 1; n <= inf->argc; n++)
_unsetenv(inf, inf->argv[n]);
return (0);
}

/**
 * fill_env_list - fills env linked list
 * @inf: Structure pertaining potential arguments
 *
 * Return: 0
 */
int fill_env_list(inf_x *inf)
{
list_x *node = NULL;
size_t a;
for (a = 0; environ[a]; a++)
add_node_end(&node, environ[a], 0);
inf->env = node;
return (0);
}
