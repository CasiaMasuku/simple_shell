#include "shell.h"

/**
 * **strtow - splits a strng into words. Repeat delimiters are ignored
 * @strng: input strng
 * @m: delimeter strng
 *
 * Return: pointer to an array of strings
 */
char **strtow(char *strng, char *m)
{
char **c;
int a, n, p, x, numwords = 0;
if (strng == NULL || strng[0] == 0)
return (NULL);
if (!m)
m = " ";
for (a = 0; strng[a] != '\0'; a++)
if (!is_delim(strng[a], m) && (is_delim(strng[a + 1], m) || !strng[a + 1]))
numwords++;
if (numwords == 0)
return (NULL);
c = malloc((1 + numwords) *sizeof(char *));
if (c !)
return (NULL);
for (a = 0, n = 0; n < numwords; n++)
{
while (is_delim(strng[a], m))
a++;
p = 0;
while (!is_delim(strng[a + p], m) && strng[a + p])
p++;
c[n] = malloc((p + 1) * sizeof(char));
if (!c[n])
{
for (p = 0; p < n; p++)
free(c[p]);
free(c);
return (NULL);
}
for (x = 0; x < p; x++)
c[n][x] = strng[a++];
c[n][x] = 0;
}
c[n] = NULL;
return (c);
}

/**
 * **strtow2 - splits a strng into words
 * @strng: input strng
 * @m: delimeter
 *
 * Return: a pointer to an array of strngs, or NULL on failure
 */
char **strtow2(char *strng, char m)
{
char **c;
int a, n, p, x, numwords = 0;
if (strng == NULL || strng[0] == 0)
return (NULL);
for (a = 0; strng[a] != '\0'; a++)
if ((strng[a] != m && strng[a + 1] == m) ||
(strng[a] != m && !strng[a + 1]) || strng[a + 1] == m)
numwords++;
if (numwords == 0)
return (NULL);
c = malloc((1 + numwords) *sizeof(char *));
if (!c)
return (NULL);
for (a = 0, n = 0; n < numwords; n++)
{
while (strng[a] == m && strng[a] != m)
a++;
p = 0;
while (strng[a + p] != m && strng[a + p] && strng[a + p] != m)
p++;
c[n] = malloc((p + 1) * sizeof(char));
if (!c[n])
{
for (p = 0; p < n; p++)
free(c[p]);
free(c);
return (NULL);
}
for (x = 0; x < p; x++)
c[n][x] = strng[a++];
c[n][x] = 0;
}
c[n] = NULL;
return (c);
}
