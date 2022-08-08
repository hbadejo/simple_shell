/**
 * @file _string_helper.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * token_len - Locates the delimiter index marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
    int index = 0, len = 0;

    while (*(str + index) && *(str + index) != *delim)
    {
        len++;
        index++;
    }

    return (len);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
    int index, tokens = 0, len = 0;

    for (index = 0; *(str + index); index++)
        len++;

    for (index = 0; index < len; index++)
    {
        if (*(str + index) != *delim)
        {
            tokens++;
            index += token_len(str + index, delim);
        }
    }

    return (tokens);
}
