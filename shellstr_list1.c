#include "shell.h"

/**
 * list_len - determines length of linked list
 * @x: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_x *x)
{
size_t a = 0;
while (x)
{
x = x->nxt;
a++;
}
return (a);
}

/**
 * list_to_strings - returns an array of strings of the list->string
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_x *head)
{
list_x *node = head;
size_t a = list_len(head), d;
char **strn;
char *string;
if (!head || !a)
return (NULL);
strn = malloc(sizeof(char *) * (a + 1));
if (!strn)
return (NULL);
for (a = 0; node; node = node->nxt, a++)
{
string = malloc(_strlen(node->string) + 1);
if (!string)
{
for (d = 0; d < a; d++)
free(strn[d]);
free(strn);
return (NULL);
}
string = _strcpy(string, node->string);
strn[a] = string;
}
strn[a] = NULL;
return (strn);
}

/**
 * print_list - prints all elements of a list_x linked list
 * @x: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_x *x)
{
size_t a = 0;
while (x)
{
_puts(cnvert_number(x->numb, 10, 0));
_putchar(':');
_putchar(' ');
_puts(x->str ? x->string : "(nil)");
_puts("\n");
x = x->nxt;
a++;
}
return (a);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @s: the next character after prefix to match
 * @node: pointer to list head
 * @preface: string to match
 *
 * Return: match node or null
 */
list_x *node_starts_with(list_x *node, char *preface, char s)
{
char *n = NULL;
while (node)
{
n = starts_with(node->string, preface);
if (n && ((s == -1) || (*n == s)))
return (node);
node = node->nxt;
}
return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node
 */
ssize_t get_node_index(list_x *head, list_x *node)
{
size_t a = 0;
while (head)
{
if (head == node)
return (a);
head = head->nxt;
a++;
}
return (-1);
