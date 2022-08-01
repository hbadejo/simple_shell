/**
 * @file tokenization.c
 * @author Hakeem BADEJO and Samuel Igwudu
 * @brief  Building a Simple shell->ALX School Assignment
 * @version 0.1
 * @date 2022-08-01
 */

#include "shell.h"

/**
 * tokenizer - Split stdin content into tokens
 * 				Strings with NULL terminated character
 * 				Append the tokens into argument vector
 *
 * @param buf: Pointer to input from stdin
 * @param origin: Pointer to input from stdin (copy of buf)
 */
void tokenizer(char *buf, char *origin)
{
	char *chips, del[] = " \n", **argv = NULL;
	int toks = 0;

	/* Tokenization of buf */
	chips = strtok(buf, del);

	/* number of argument passed */
	while (chips)
	{
		toks++;
		chips = strtok(NULL, del);
	}
	toks++;

	/* memory allocation for argv contents */
	argv = malloc(sizeof(char *) * toks);

	/* Tokenization of origin */
	chips = strtok(origin, del);

	/* Including NULL to argument vector
	 * copying null terminated string to arg vector */
	for (int i = 0; chips; i++)
	{
		argv[i] = malloc(sizeof(char *) * strlen(chips));
		strcpy(argv[i], chips);
		chips = strtok(NULL, del);

		if (!chips)
			argv[++i] = NULL;
	}

	/* calling rendering function */
	render_cmd(argv);
	free(chips);
	free(argv);
}
