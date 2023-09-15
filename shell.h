#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @string: a string
 * @numb: number's field
 * @nxt: next node pointer
 */
typedef struct liststr
{
	int numb;
	struct liststr *nxt;
	char *string;
} list_x;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_numb: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @hist: the history node
 * @f.name: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_numb;
	int linecount_flag;
	char *f.name;
	int status;
	list_x *env;
	list_x *hist;
	list_x *alias;
	char **environ;
	int env_changed;

	char **cmd_buf;
	int readfd;
	int cmd_buf_type;
	int histcount;
} inf_x;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@kind: builtin command flag
 *@functn: considered function
 */
typedef struct builtin
{
	char *kind;
	int (*functn)(inf_x *);
} builtin_table;


/* shell_hs .c */
int hsh(inf_x *, char **);
int find_builtin(inf_x *);
void find_cmd(inf_x *);
void fork_cmd(inf_x *);

/* shell_pth.c */
int is_cmd(inf_x *, char *);
char *dup_chars(char *, int, int);
char *find_path(inf_x *, char *, char *);

/* lphshell.c */
int loophsh(char **);

/* string_f_err.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *string, int fd);

/* shell_str_funct.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* shell_str_funct1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* shell_str_funct2.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* shell_str_funct3.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* shell_memf.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* shell_memf1.c */
int bfree(void **);

/* shell_funct.c */
int interactive(inf_x *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* shell_funct1.c */
int _erratoi(char *);
void print_error(inf_x *, char *);
int print_d(int, int);
char *cnvert_number(long int, int, int);
void erase_comments(char *);

/* fixed_emlt.c */
int _shellexit(inf_x *);
int _shellcd(inf_x *);
int _shellhelp(inf_x *);

/* fixed_emlt1.c */
int _shellhist(inf_x *);
int _shellalias(inf_x *);

/* getline.c module */
ssize_t get_input(inf_x *);
int _getline(inf_x *, char **, size_t *);
void sigintHandler(int);

/* s_shell_infrmtn */
void set_info(inf_x *, char **);
void free_info(inf_x *, int);
void clear_info(inf_x *);

/*envrmnt.c  */
char *_getenv(inf_x *, const char *);
int _shellenv(inf_x *);
int _shellsetenv(inf_x *);
int _shellunsetenv(inf_x *);
int fill_env_list(inf_x *);

/* envrmnt1.c */
char **get_environ(inf_x *);
int _unsetenv(inf_x *, char *);
int _setenv(inf_x *, char *, char *);

/* shell_io_f.c */
char *get_hist_file(inf_x *inf);
int write_hist(inf_x *inf);
int read_hist(inf_x *inf);
int build_hist_list(inf_x *inf, char *buf, int linecount);
int renumber_hist(inf_x *inf);

/* shellstr_list.c */
list_x *add_node(list_x **, const char *, int);
list_x *add_node_end(list_x **, const char *, int);
size_t print_list_str(const list_x *);
int remov_node_at_index(list_x **, unsigned int);
void free_list(list_x **);

/* shellstr_list1.c */
size_t list_len(const list_x *);
char **list_to_strings(list_x *);
size_t print_list(const list_x *);
list_x *node_starts_with(list_x *, char *, char);
size_t get_node_index(list_x *, list_x *);

/* shellchain.c */
int is_chain(inf_x *, char *, size_t *);
void check_chain(inf_x *, char *, size_t *, size_t, size_t);
int replace_alias(inf_x *);
int replace_vars(inf_x *);
int replace_string(char **, char *);

#endif
