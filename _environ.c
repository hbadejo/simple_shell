/**
 * @file _environ.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environ;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 1));
	if (!new_environ)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environ[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environ[index])
		{
			for (index--; index >= 0; index--)
				free(new_environ[index]);
			free(new_environ);
			return (NULL);
		}
		_strcpy(new_environ[index], environ[index]);
	}
	new_environ[index] = NULL;

	return (new_environ);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}

/**
 * get_env_val - Gets the value corresponding to an environmental variable.
 * @start: The environmental variable to search for.
 * @len: The length of the environmental variable.
 *
 * Return: environ variable or empty str if nothing is found.
 */
char *get_env_val(char *start, int len)
{
	char **var_addr, *replacement = NULL, *intr, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, start, len);

	var_addr = _getenv(var);
	free(var);
	if (var_addr)
	{
		intr = *var_addr;
		while (*intr != '=')
			intr++;
		intr++;
		replacement = malloc(_strlen(intr) + 1);
		if (replacement)
			_strcpy(replacement, intr);
	}

	return (replacement);
}

/**
 * free_argv - Frees up memory taken by argv.
 * @argv: A null-terminated double pointer containing commands/arguments.
 * @start: A pointer to the pointer of  argv.
 */
void free_argv(char **argv, char **start)
{
	size_t i;

	for (i = 0; argv[i] || argv[i + 1]; i++)
		free(argv[i]);
	free(start);
}
