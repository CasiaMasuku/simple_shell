#include "shell.h"

/**
 * _shellhist - displays the history list, one command by line
 * @inf: Structure pertaining potential arguments
 *
 * Return: 0
 */
int _shellhist(inf_x *inf)
{
print_list(inf->hist);
return (0);
}

/**
 * unset_alias - sets alias to string
 * @inf: parameter struct
 * @string: considered string alias
 *
 * Return: 0 on success
 */
int unset_alias(inf_x *inf, char *string)
{
char *n, s int ret;
n = _strchr(string, '=');
if (!n)
return (1);
s = *n;
*n = 0;
ret = remov_node_at_index(&(inf->alias),
get_node_index(inf->alias, node_starts_with(inf->alias, string, -1)));
*n = s;
return (ret);
}

/**
 * set_alias - sets alias to string
 * @inf: parameter struct
 * @string: the string alias
 *
 * Return: 0 on success
 */
int set_alias(inf_x *inf, char *string)
{
char *n;
n = _strchr(string, '=');
if (!n)
return (1);
if (!*++n)
return (unset_alias(inf, string));
unset_alias(inf, string);
return (add_node_end(&(inf->alias), string, 0) == NULL);
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
 * @inf: Structure pertaining potential arguments
 *
 *  Return: Always 0
 */
int _shellalias(inf_x *inf)
{
int a = 0;
char *n = NULL;
list_x *node = NULL;
if (inf->argc == 1)
{
node = inf->alias;
while (node)
{
print_alias(node);
node = node->nxt;
}
return (0);
}
for (a = 1; inf->argv[a]; a++)
{
n = _strchr(inf->argv[a], '=');
if (n)
set_alias(inf, inf->argv[a]);
else
print_alias(node_starts_with(inf->alias, inf->argv[a], '='));
}
return (0);
}
