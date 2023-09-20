#include "shell.h"

/**
 * is_chain - tests if the current char in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: the char buffer
 * @n: address of current position
 *
 * Return: 1 if chain delimeter
 */
int is_chain(info_t *info, char *buf, size_t *n)
{
size_t i = *n;
if (buf[i] == '|' && buf[i + 1] == '|')
{
buf[i] = 0;
i++;
info->cmd_buf_type = CMD_OR;
}
else if (buf[i] == '&' && buf[i + 1] == '&')
{
buf[i] = 0;
i++;
info->cmd_buf_type = CMD_AND;
}
else if (buf[i] == ';')
{
buf[i] = 0;
info->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*n = i;
return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @i: address of current position in buf
 * @n: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *i, size_t n, size_t len)
{
size_t t = *i;
if (info->cmd_buf_type == CMD_AND)
{
if (info->status)
{
buf[n] = 0;
t = len;
}
}
if (info->cmd_buf_type == CMD_OR)
{
if (!info->status)
{
buf[n] = 0;
t = len;
}
}
*i = t;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced
 */
int replace_alias(info_t *info)
{
int n;
list_x *node;
char *i;
for (n = 0; n < 10; n++)
{
node = node_starts_with(info->alias, info->argv[0], '=');
if (!node)
return (0);
free(info->argv[0]);
i = _strchr(node->string, '=');
if (!i)
return (0);
i = _strdup(i + 1);
if (!i)
return (0);
info->argv[0] = i;
}
return (1);
}

/**
 * replace_vars - replaces vars
 * @info: considered parameter struct
 *
 * Return: 1 if replaced
 */
int replace_vars(info_t *info)
{
int a = 0;
list_x *node;
for (a = 0; info->argv[a]; a++)
{
if (info->argv[a][0] != '$' || !info->argv[a][1])
continue;
if (!_strcmp(info->argv[a], "$?"))
{
replace_string(&(info->argv[a]),
_strdup(cnvert_number(info->status, 10, 0)));
continue;
}
if (!_strcmp(info->argv[a], "$$"))
{
replace_string(&(info->argv[a]),
_strdup(cnvert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(info->env, &info->argv[a][1], '=');
if (node)
{
replace_string(&(info->argv[a]),
_strdup(_strchr(node->string, '=') + 1));
continue;
}
replace_string(&info->argv[a], _strdup(""));
}
return (0);
}

/**
 * replace_string - replaces string
 * @new: new string
 * @old: address of old string
 *
 * Return: 1 if replaced
 */
int replace_string(char **old, char *new)
{
free(*old);
*old = new;
return (1);
}
