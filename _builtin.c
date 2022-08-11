/**
 * @file _builtin.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"
/**
 * get_builtin - Matches a command with a corresponding
 *               builtin function.
 * @command: The command to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *command))(char **argv, char **start)
{
	builtin_t funcs[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"help", builtin_help},
		{NULL, NULL}};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, command) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * builtin_exit - Causes normal process termination
 *                for the builtin shell.
 * @argv: An array of arguments containing the exit value.
 * @start: A pointer to the pointer of  argv.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int builtin_exit(char **argv, char **start)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (argv[0])
	{
		if (argv[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; argv[0][i]; i++)
		{
			if (i <= len_of_int && argv[0][i] >= '0' && argv[0][i] <= '9')
				num = (num * 10) + (argv[0][i] - '0');
			else
				return (gen_error(--argv, 2));
		}
	}
	else
	{
		ireturn(-3);
	}
	if (num > max - 1)
		return (gen_error(--argv, 2));
	argv -= 1;
	free_argv(argv, start);
	free_env();
	free_alias_list(ll_aliases);
	exit(num);
}

/**
 * builtin_cd - Changes the current directory of the builtin process.
 * @argv: An array of arguments.
 * @start: A pointer to the pointer of  argv.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int builtin_cd(char **argv, char __attribute__((__unused__)) * *start)
{
	char **dir_info, *new_com = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (argv[0])
	{
		if (*(argv[0]) == '-' || _strcmp(argv[0], "--") == 0)
		{
			if ((argv[0][1] == '-' && argv[0][2] == '\0') ||
				argv[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (gen_error(argv, 2));
			}
		}
		else
		{
			if (stat(argv[0], &dir) == 0 && S_ISDIR(dir.st_mode) && ((dir.st_mode & S_IXUSR) != 0))
				chdir(argv[0]);
			else
			{
				free(oldpwd);
				return (gen_error(argv, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (builtin_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (builtin_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (argv[0] && argv[0][0] == '-' && argv[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_com, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * builtin_help - Displays information about builtin builtin commands.
 * @argv: An array of arguments.
 * @start: A pointer to the start of argv.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int builtin_help(char **argv, char __attribute__((__unused__)) * *start)
{
	if (!argv[0])
		help_all();
	else if (_strcmp(argv[0], "alias") == 0)
		help_alias();
	else if (_strcmp(argv[0], "cd") == 0)
		help_cd();
	else if (_strcmp(argv[0], "exit") == 0)
		help_exit();
	else if (_strcmp(argv[0], "env") == 0)
		help_env();
	else if (_strcmp(argv[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(argv[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(argv[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}

/**
 * builtin_setenv - Changes or adds an environmental variable to the PATH.
 * @argv: An array of arguments passed to the shell.
 * @start: A pointer to the pointer of  argv.
 * Description: argv[1] is the name of the new or existing PATH variable.
 *              argv[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int builtin_setenv(char **argv, char __attribute__((__unused__)) * *start)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!argv[0] || !argv[1])
		return (gen_error(argv, -1));

	new_value = malloc(_strlen(argv[0]) + 1 + _strlen(argv[1]) + 1);
	if (!new_value)
		return (gen_error(argv, -1));
	_strcpy(new_value, argv[0]);
	_strcat(new_value, "=");
	_strcat(new_value, argv[1]);

	env_var = _getenv(argv[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (gen_error(argv, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}
