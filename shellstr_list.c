#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer
 * @numb: node index used by history
 * @string: string field of node
 *
 * Return: size of list
 */
list_x *add_node(list_x **head, const char *string, int numb)
{
list_ *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(list_x));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(list_x));
new_head->numb = numb;
if (string)
{
new_head->string = _strdup(string);
if (!new_head->string)
{
free(new_head);
return (NULL);
}
}
new_head->nxt = *head;
*head = new_head;
return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @string: string field of node
 * @head: address of pointer to head node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_x *add_node_end(list_x **head, const char *string, int numb)
{
list_x *new_node, *node;
if (!head)
return (NULL);
node = *head;
new_node = malloc(sizeof(list_x));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_x));
new_node->numb = numb;
if (string)
{
new_node->string = _strdup(string);
if (!new_node->string)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->nxt)
node = node->nxt;
node->nxt = new_node;
}
else
{
*head = new_node;
return (new_node);
}
}

/**
 * print_list_str - prints only the string element of a list_x linked list
 * @x: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_x *x)
{
size_t a = 0;
while (x)
{
_puts(x->string ? x->string : "(nil)");
_puts("\n");
x = x->nxt;
a++;
}
return (a);
}

/**
 * remov_node_at_index - removes node at given index
 * @head: address of pointer to first node
 * @index: index of node to remove
 *
 * Return: 1 on success
 */
int remov_node_at_index(list_x **head, unsigned int index)
{
list_x *node, *prev_node;
unsigned int a = 0;
if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->nxt;
free(node->string);
free(node);
return (1);
}
node = *head;
while (node)
{
if (a == index)
{
prev_node->nxt = node->nxt;
free(node->string);
free(node);
return (1);
}
a++;
prev_node = node;
node = node->nxt;
}
return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_x **head_ptr)
{
list_x *node, *nxt_node, *head;
if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->nxt;
free(node->string);
free(node);
node = next_node;
}
*head_ptr = NULL;
}
