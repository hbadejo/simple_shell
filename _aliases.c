/**
 * @file _aliases.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * builtin_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @argv: An array of arguments.
 * @start: A pointer to the pointer of  argv.
 *
 * Return: return 0 on success. On error returns -1
 */
int builtin_alias(char **argv, char __attribute__((__unused__)) * *start)
{
    alias_t *intr = ll_aliases;
    int i, ret_val = 0;
    char *value;

    if (!argv[0])
    {
        while (intr)
        {
            print_alias(intr);
            intr = intr->next;
        }
        return (ret_val);
    }

    for (i = 0; argv[i]; i++)
    {
        intr = ll_aliases;
        value = _strchr(argv[i], '=');
        if (!value)
        {
            while (intr)
            {
                if (_strcmp(argv[i], intr->name) == 0)
                {
                    print_alias(intr);
                    break;
                }
                intr = intr->next;
            }
            if (!intr)
                ret_val = gen_error(argv + i, 1);
        }
        else
            set_alias(argv[i], value);
    }
    return (ret_val);
}

/**
 * set_alias - Set or creates a new alias with 'name' and 'value'.
 * @arg: Name of the alias.
 * @ex_val: Value of the alias. First character is a '='.
 * Return: return void
 */
void set_alias(char *arg, char *ex_val)
{
    alias_t *intr = ll_aliases;
    int len, i, n;
    char *new_val;

    *ex_val = '\0';
    ex_val++;
    len = _strlen(ex_val) - _strspn(ex_val, "'\"");
    new_val = malloc(sizeof(char) * (len + 1));
    if (!new_val)
        return;
    for (i = 0, n = 0; ex_val[i]; i++)
    {
        if (ex_val[i] != '\'' && ex_val[i] != '"')
            new_val[n++] = ex_val[i];
    }
    new_val[n] = '\0';
    while (intr)
    {
        if (_strcmp(arg, intr->name) == 0)
        {
            free(intr->value);
            intr->value = new_val;
            break;
        }
        intr = intr->next;
    }
    if (!intr)
        appendAlias(&ll_aliases, arg, new_val);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 *
 * @alias: Pointer to an alias.
 * Return: return void
 */
void print_alias(alias_t *alias)
{
    char *new_str;
    int len = _strlen(alias->name) + _strlen(alias->value) + 4;

    new_str = malloc(sizeof(char) * (len + 1));
    if (!new_str)
        return;
    _strcpy(new_str, alias->name);
    _strcat(new_str, "='");
    _strcat(new_str, alias->value);
    _strcat(new_str, "'\n");

    write(STDOUT_FILENO, new_str, len);
    free(new_str);
}
/**
 * replace_aliases - Replace matching alias with it values
 *
 * @argv: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **argv)
{
    alias_t *intr;
    char *new_val;

    if (_strcmp(argv[0], "alias") == 0)
        return (argv);
    for (int i = 0; argv[i]; i++)
    {
        intr = ll_aliases;
        while (intr)
        {
            if (_strcmp(argv[i], intr->name) == 0)
            {
                new_val = malloc(sizeof(char) * (_strlen(intr->value) + 1));
                if (!new_val)
                {
                    free_argv(argv, argv);
                    return (NULL);
                }
                _strcpy(new_val, intr->value);
                free(argv[i]);
                argv[i] = new_val;
                i--;
                break;
            }
            intr = intr->next;
        }
    }

    return (argv);
}
