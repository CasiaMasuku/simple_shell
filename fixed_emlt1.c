#include "shell.h"

/**
 * _shellhist - displays the history list, one command by line
 * @info: Structure pertaining potential arguments
 *
 * Return: 0
 */
int _shellhist(info_t *info)
{
print_list(info->hist);
return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @string: considered string alias
 *
 * Return: 0 on success
 */
int unset_alias(info_t *info, char *string)
{
char *n, s;
int ret;
n = _strchr(string, '=');
if (!n)
return (1);
s = *n;
*n = 0;
ret = remov_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, string, -1)));
*n = s;
return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @string: the string alias
 *
 * Return: 0 on success
 */
int set_alias(info_t *info, char *string)
{
char *n;
n = _strchr(string, '=');
if (!n)
return (1);
if (!*++n)
return (unset_alias(info, string));
unset_alias(info, string);
return (add_node_end(&(info->alias), string, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: 0 on success
 */
int print_alias(list_x *node)
{
char *n = NULL, *i = NULL;
if (node)
{
n = _strchr(node->string, '=');
for (i = node->string; i <= n; i++)
_putchar(*i);
_putchar('\'');
_puts(n + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * _shellalias - imitate the alias fixed(builtin)
 * @info: Structure pertaining potential arguments
 *
 *  Return: Always 0
 */
int _shellalias(info_t *info)
{
int a = 0;
char *n = NULL;
list_x *node = NULL;
if (info->argc == 1)
{
node = info->alias;
while (node)
{
print_alias(node);
node = node->nxt;
}
return (0);
}
for (a = 1; info->argv[a]; a++)
{
n = _strchr(info->argv[a], '=');
if (n)
set_alias(info, info->argv[a]);
else
print_alias(node_starts_with(info->alias, info->argv[a], '='));
}
return (0);
}
