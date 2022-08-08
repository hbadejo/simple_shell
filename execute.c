/**
 * @file execute.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"
/**
 * run_argv - Calls the execution of a command.
 * @argv: An array of arguments.
 * @start: A pointer to the pointer of  argv.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int run_argv(char **argv, char **start, int *exe_ret)
{
    int ret_val, i;
    int (*builtin)(char **argv, char **start);

    builtin = get_builtin(argv[0]);

    if (builtin)
    {
        ret_val = builtin(argv + 1, start);
        if (ret_val != EXIT)
            *exe_ret = ret_val;
    }
    else
    {
        *exe_ret = runprog(argv, start);
        ret_val = *exe_ret;
    }

    hist++;

    for (i = 0; argv[i]; i++)
        free(argv[i]);

    return (ret_val);
}

/**
 * handle_argv - Gets, calls, and runs the execution of a command.
 * @exe_ret: last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed command.
 */
int handle_argv(int *exe_ret)
{
    int ret_val = 0, index;
    char **argv, *line = NULL, **start;

    line = get_argv(line, exe_ret);
    if (!line)
        return (END_OF_FILE);

    argv = _strtok(line, " ");
    free(line);
    if (!argv)
        return (ret_val);
    if (check_argv(argv) != 0)
    {
        *exe_ret = 2;
        free_argv(argv, argv);
        return (*exe_ret);
    }
    start = argv;

    for (index = 0; argv[index]; index++)
    {
        if (_strncmp(argv[index], ";", 1) == 0)
        {
            free(argv[index]);
            argv[index] = NULL;
            ret_val = call_argv(argv, start, exe_ret);
            argv = &argv[++index];
            index = 0;
        }
    }
    if (argv)
        ret_val = call_argv(argv, start, exe_ret);

    free(start);
    return (ret_val);
}

/**
 * get_argv - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *get_argv(char *line, int *exe_ret)
{
    size_t n = 0;
    ssize_t read;
    // char *prompt = _strcat(*_getenv("LOGNAME"), "%% ");
    char shell_prompt[15] = "haksam";
    char *prompt = _strcat(shell_prompt, " $ ");

    if (line)
        free(line);

    read = _getline(&line, &n, STDIN_FILENO);
    if (read == -1)
        return (NULL);
    if (read == 1)
    {
        hist++;
        if (isatty(STDIN_FILENO))
            write(STDOUT_FILENO, prompt, 15);
        return (get_argv(line, exe_ret));
    }

    line[read - 1] = '\0';
    variable_replacement(&line, exe_ret);
    handle_line(&line, read);

    return (line);
}

/**
 * call_argv - Partitions operators from commands and calls them.
 * @argv: An array of arguments.
 * @start: A pointer to the pointer of  argv.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: The return value of the last executed command.
 */
int call_argv(char **argv, char **start, int *exe_ret)
{
    int ret_val, index;

    if (!argv[0])
        return (*exe_ret);
    for (index = 0; argv[index]; index++)
    {
        if (_strncmp(argv[index], "||", 2) == 0)
        {
            free(argv[index]);
            argv[index] = NULL;
            argv = replace_aliases(argv);
            ret_val = run_argv(argv, start, exe_ret);
            if (*exe_ret != 0)
            {
                argv = &argv[++index];
                index = 0;
            }
            else
            {
                for (index++; argv[index]; index++)
                    free(argv[index]);
                return (ret_val);
            }
        }
        else if (_strncmp(argv[index], "&&", 2) == 0)
        {
            free(argv[index]);
            argv[index] = NULL;
            argv = replace_aliases(argv);
            ret_val = run_argv(argv, start, exe_ret);
            if (*exe_ret == 0)
            {
                argv = &argv[++index];
                index = 0;
            }
            else
            {
                for (index++; argv[index]; index++)
                    free(argv[index]);
                return (ret_val);
            }
        }
    }
    argv = replace_aliases(argv);
    ret_val = run_argv(argv, start, exe_ret);
    return (ret_val);
}

/**
 * runprog - Executes a command in a child process.
 * @argv: Argument vector.
 * @start: A pointer to the pointer of argument vector.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int runprog(char **argv, char **start)
{
    pid_t child_pid;
    int status, flag = 0, ret_val = 0;
    char *command = argv[0];

    if (command[0] != '/' && command[0] != '.')
    {
        flag = 1;
        command = get_location(command);
    }

    if (!command || (access(command, F_OK) == -1))
    {
        if (errno == EACCES)
            ret_val = (gen_error(argv, 126));
        else
            ret_val = (gen_error(argv, 127));
    }
    else
    {
        child_pid = fork();
        if (child_pid == -1)
        {
            if (flag)
                free(command);
            perror("Error child:");
            return (1);
        }
        if (child_pid == 0)
        {
            execve(command, argv, environ);
            if (errno == EACCES)
                ret_val = (gen_error(argv, 126));
            free_env();
            free_argv(argv, start);
            free_alias_list(ll_aliases);
            _exit(ret_val);
        }
        else
        {
            wait(&status);
            ret_val = WEXITSTATUS(status);
        }
    }
    if (flag)
        free(command);
    return (ret_val);
}
