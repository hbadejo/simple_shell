/**
 * @file getline.c
 * @author Hakeem BADEJO and Samuel Igwudu
 * @brief  Building a Simple shell->ALX School Assignment
 * @version 0.1
 * @date 2022-08-01
 */

#include "shell.h"

/**
 * read_cmd - Read input from stdin through the terminal
 * 				duplicate it for tokenization
 *
 * return: Return void
 */
void read_cmd(void)
{
	size_t buf_size;  /* unsigned int */
	ssize_t readline; /* singed int */
	char *buf = NULL, *origin;

	printf("ready to process command %% ");

	/* getline returns -1 if failed
	 * returns number of agr on success
	 * input from standard input-> keyboard*/
	readline = getline(&buf, &buf_size, stdin);

	if (readline == -1)
		printf("failed to read from stdin. terminating session...");

	/* on success */
	origin = malloc(sizeof(char *) * readline);
	strcpy(origin, buf);

	/* tokenization of argv */
	tokenizer(buf, origin);

	/* releasing memory -> prevent meory leak */
	free(buf);
	free(origin);
}
