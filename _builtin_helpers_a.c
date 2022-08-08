/**
 * @file _builtin_helpers_a.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * help_env - Displays information on the builtin builtin command 'env'.
 */
void help_env(void)
{
    char *msg = "env: env\n\tPrints the current environment.\n";

    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_setenv - Displays information on the builtin builtin command 'setenv'.
 */
void help_setenv(void)
{
    char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "environment variable, or modifies an existing one.\n\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "\tUpon failure, prints a message to stderr.\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_unsetenv - Displays information on the builtin builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
    char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "environmental variable.\n\n\tUpon failure, prints a ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "message to stderr.\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
}

/**
 * help_help - Displays information on the builtin builtin command 'help'.
 */
void help_help(void)
{
    char *msg = "help: help\n\tSee all possible builtin builtin commands.\n";

    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
    write(STDOUT_FILENO, msg, _strlen(msg));
    msg = "builtin command.\n";
    write(STDOUT_FILENO, msg, _strlen(msg));
}
