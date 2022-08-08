/**
 * @file main.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
    int ret_val = 0, retn;
    int *exe_ret = &retn;
    char shell_prompt[15] = "haksam";
    char *prompt = _strcat(shell_prompt, " $ "), *new_com = "\n";

    name = argv[0];
    hist = 1;
    ll_aliases = NULL;
    signal(SIGINT, sig_handler);

    *exe_ret = 0;
    environ = _copyenv();
    if (!environ)
        exit(-100);

    if (argc != 1)
    {
        ret_val = file_stdin(argv[1], exe_ret);
        free_env();
        free_alias_list(ll_aliases);
        return (*exe_ret);
    }

    if (!isatty(STDIN_FILENO))
    {
        while (ret_val != END_OF_FILE && ret_val != EXIT)
            ret_val = handle_argv(exe_ret);
        free_env();
        free_alias_list(ll_aliases);
        return (*exe_ret);
    }

    while (1)
    {
        write(STDOUT_FILENO, prompt, 15);
        ret_val = handle_argv(exe_ret);
        if (ret_val == END_OF_FILE || ret_val == EXIT)
        {
            if (ret_val == END_OF_FILE)
                write(STDOUT_FILENO, new_com, 1);
            free_env();
            free_alias_list(ll_aliases);
            exit(*exe_ret);
        }
    }

    free_env();
    free_alias_list(ll_aliases);
    return (*exe_ret);
}
