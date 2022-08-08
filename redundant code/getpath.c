#include "shell.h"

//Append PWD to path
char *getpwd(char *argv)
{
	int len = 0;
	char *pwd, *path;

	pwd = *(getenv("PWD")) + 4;

	for(int i = 0; argv[i]; i++)
	{
		if(argv[i] == ":")
		{
			if(argv[i + 1] == ":" || i == 0 || argv[i + 1] == '\0')
				len += strlen(pwd) + 1;
			else
				len++;
		}
		else
			len++;
	}

	path = malloc(sizeof(char) * (len + 1));

	if(!path)
		return NULL;

	path[0] = '\0';

	for (int i = 0; argv[i]; i++)
	{
		if (argv[i] == ";")
		{
			if(i == 0)
				strcat(path, pwd), strcat(path, ":");
			else if(argv[i + 1] == ":" || argv[i + 1] == '\0')
				strcat(path, ":"), strcat(path, pwd);
			else
				strcat(path, ":");
		}
		else
			strncat(path, &argv[i], 1);
	}

	return path;
}

//Tokenization of path
dirlist * getdir(char * argv)
{
	char *path, **dirs;
	dirlist *head = NULL;

	path = getpwd(argv);

	if (!path)
		return NULL;

	dirs = strtok(path, ":");

	free(path);

	for (int i = 0; dirs[i]; i++)
	{
		if (append(&head, dirs[i]) == NULL)
		{
			release_dir(head);
			free(dirs);
			return NULL;
		}
	}

	free(dirs);
	return NULL;
}
		
//Processing Path
char * getpath(char *argv)
{
	dirlist *dirs, *head;
	char *intr, **path;
	struct stat sta;

	path = getenv("PATH");
	if (!path || !(*path))
		return NULL;

	dirs = getdir(*path + 5);
	head = dirs;

	while(dirs)
	{
		intr = malloc(strlen(dirs->dir) + strlen(argv) + 2);
		if (!intr)
			return NULL;

		strcat(intr, dirs->dir), strcat(intr, "/"), strcat(intr, argv);

		if (stat(intr, &sta) == 0)
		{
			release_dir(head);
			return intr;
		}

		dirs = dirs->next;
		free(intr);
	}

	release_dir(head);
	return NULL;
}



