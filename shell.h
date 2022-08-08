#ifndef SHELL_H
#define SHELL_H

/**
 * @file shell.h
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

/* -----------------Header files----------------- */
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* ---------------struct declaration-------------------- */
/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **start);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* -----------------Global variables----------------- */
extern char **environ;
char *name;
int hist;
alias_t *ll_aliases;

/* ------------------Functions Declaration--------------- */

/* execute */
int run_argv(char **argv, char **start, int *exe_ret);
int handle_argv(int *exe_ret);
char *get_argv(char *line, int *exe_ret);
int call_argv(char **argv, char **start, int *exe_ret);
int runprog(char **argv, char **start);

/* _string */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char **_strtok(char *line, char *delim);
char *_strcat(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strncat(char *dest, const char *src, size_t n);
int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);

/* helper_a */
char *get_pid(void);
void variable_replacement(char **line, int *exe_ret);
void sig_handler(int sig);

/* builtin */
int builtin_env(char **argv, char __attribute__((__unused__)) * *start);
int builtin_unsetenv(char **argv, char __attribute__((__unused__)) * *start);
int (*get_builtin(char *command))(char **argv, char **start);
int builtin_exit(char **argv, char **start);
int builtin_cd(char **argv, char __attribute__((__unused__)) * *start);
int builtin_help(char **argv, char __attribute__((__unused__)) * *start);
int builtin_setenv(char **argv, char __attribute__((__unused__)) * *start);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_help(void);
void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);

/* Aliases */
int builtin_alias(char **argv, char __attribute__((__unused__)) * *start);
void set_alias(char *arg, char *ex_val);
void print_alias(alias_t *alias);
char **replace_aliases(char **argv);

/* environs */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);
char *get_env_val(char *start, int len);
void free_argv(char **argv, char **start);

/* args_processes */
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);
void handle_line(char **line, ssize_t read);
int check_argv(char **argv);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* mem_handler */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void assign_lineptr(char **lineptr, size_t *n, char *buffer, size_t b);

/* file input */
int cant_open(char *file_path);
int file_stdin(char *file_path, int *exe_ret);

/* errors */
char *error_env(char **argv);
char *error_1(char **argv);
char *error_2_exit(char **argv);
char *error_2_cd(char **argv);
char *error_2_syntax(char **argv);
int num_len(int num);
char *_itoa(int num);
int gen_error(char **argv, int err);
char *error_126(char **argv);
char *error_127(char **argv);

/* Path handler */
char *get_location(char *command);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/* linked list */
alias_t *appendAlias(alias_t **head, char *name, char *value);
list_t *appendNode(list_t **head, char *dir);
void free_alias_list(alias_t *head);
void free_list(list_t *head);
#endif /* SHELL_H */
