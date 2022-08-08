/**
 * @file shell.h
 * @author Hakeem BADEJO and Samuel Igwudu
 * @brief  Building a Simple shell->ALX School Assignment
 * @version 0.1
 * @date 2022-08-01
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SHELL_H
#define SHELL_H

/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* function declaration */

void render_cmd(char **argv);
void tokenizer(char *buf, char *origin);
void read_cmd(void);

#endif /* SHELL_H */
