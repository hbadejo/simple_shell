/**
 * @file _builtin_b.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * builtin_env - Prints the current environment.
 * @argv: An array of arguments passed to the shell.
 * @start: A pointer to the pointer of  argv.
 *
 * Return: zero for success and -1 for fail
 */
int builtin_env(char **argv, char __attribute__((__unused__)) * *start)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)argv;
	return (0);
}

/**
 * builtin_unsetenv - Deletes an environmental variable from the PATH.
 * @argv: An array of arguments passed to the shell.
 * @start: A pointer to the pointer of  argv.
 * Description: argv[1] is the PATH variable to remove.
 *
 * Return: zero for success and -1 for fail
 */
int builtin_unsetenv(char **argv, char __attribute__((__unused__)) * *start)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!argv[0])
		return (gen_error(argv, -1));
	env_var = _getenv(argv[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (gen_error(argv, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
