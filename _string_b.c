/**
 * @file _string_b.c
 * @author Hakeem BADEJO
 *         Samuel IGWUDU
 * @brief Build your own SHELL : ALX Assignment
 */

#include "shell.h"

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The length of the character string.
 */
int _strlen(const char *s)
{
    int length = 0;

    if (!s)
        return (length);
    for (length = 0; s[length]; length++)
        ;
    return (length);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
    size_t i;

    for (i = 0; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
    char **ptr;
    int index = 0, tokens, t, letters, l;

    tokens = count_tokens(line, delim);
    if (tokens == 0)
        return (NULL);

    ptr = malloc(sizeof(char *) * (tokens + 2));
    if (!ptr)
        return (NULL);

    for (t = 0; t < tokens; t++)
    {
        while (line[index] == *delim)
            index++;

        letters = token_len(line + index, delim);

        ptr[t] = malloc(sizeof(char) * (letters + 1));
        if (!ptr[t])
        {
            for (index -= 1; index >= 0; index--)
                free(ptr[index]);
            free(ptr);
            return (NULL);
        }

        for (l = 0; l < letters; l++)
        {
            ptr[t][l] = line[index];
            index++;
        }

        ptr[t][l] = '\0';
    }
    ptr[t] = NULL;
    ptr[t + 1] = NULL;

    return (ptr);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
    char *destTemp;
    const char *srcTemp;

    destTemp = dest;
    srcTemp = src;

    while (*destTemp != '\0')
        destTemp++;

    while (*srcTemp != '\0')
        *destTemp++ = *srcTemp++;
    *destTemp = '\0';
    return (dest);
}
