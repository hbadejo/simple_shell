/**
 * @file runcmd.c
 * @author Hakeem BADEJO and Samuel Igwudu
 * @brief  Building a Simple shell->ALX School Assignment
 * @version 0.1
 * @date 2022-08-01
 */

#include "shell.h"

/**
 * render_cmd - Process tokenized string and run terminal cmd.
 *
 * return: Return void
 */
void render_cmd(char **argv)
{
	char pathA[30] = "/bin/", pathB[30] = "/usr/bin/";

	strcat(pathA, argv[0]);
	if (execve(pathA, argv, NULL) == -1)
	{
		strcat(pathB, argv[0]);
		if (execve(pathB, argv, NULL) == -1)
		{
			perror("command not found");
			return;
		}
	}
}
