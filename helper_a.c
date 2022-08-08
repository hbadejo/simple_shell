/**
 * @file helper_a.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
    size_t i = 0;
    char *buffer;
    ssize_t file;

    file = open("/proc/self/stat", O_RDONLY);
    if (file == -1)
    {
        perror("Cant read file");
        return (NULL);
    }
    buffer = malloc(120);
    if (!buffer)
    {
        close(file);
        return (NULL);
    }
    read(file, buffer, 120);
    while (buffer[i] != ' ')
        i++;
    buffer[i] = '\0';

    close(file);
    return (buffer);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
    int k = 0, len;
    char *replacement = NULL, *old_com = NULL, *new_com;

    old_com = *line;
    for (int j = 0; old_com[j]; j++)
    {
        if (old_com[j] == '$' && old_com[j + 1] &&
            old_com[j + 1] != ' ')
        {
            if (old_com[j + 1] == '$')
            {
                replacement = get_pid();
                k = j + 2;
            }
            else if (old_com[j + 1] == '?')
            {
                replacement = _itoa(*exe_ret);
                k = j + 2;
            }
            else if (old_com[j + 1])
            {
                /* extract the variable name to search for */
                for (k = j + 1; old_com[k] &&
                                old_com[k] != '$' &&
                                old_com[k] != ' ';
                     k++)
                    ;
                len = k - (j + 1);
                replacement = get_env_val(&old_com[j + 1], len);
            }
            new_com = malloc(j + _strlen(replacement) + _strlen(&old_com[k]) + 1);
            if (!line)
                return;
            new_com[0] = '\0';
            _strncat(new_com, old_com, j);
            if (replacement)
            {
                _strcat(new_com, replacement);
                free(replacement);
                replacement = NULL;
            }
            _strcat(new_com, &old_com[k]);
            free(old_com);
            *line = new_com;
            old_com = new_com;
            j = -1;
        }
    }
}

/**
 * sig_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
    // char *prompt = _strcat(*_getenv("LOGNAME"), "%% ");
    char shell_prompt[15] = "haksam";
    char *prompt = _strcat(shell_prompt, " $ ");

    (void)sig;
    signal(SIGINT, sig_handler);
    write(STDIN_FILENO, prompt, 15);
}
