#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * change_dir - change directory
 * @directory: directory
 * @return void
 */
void change_dir(char *directory)
	{
	if (*directory == '\0')
		directory = getenv("HOME");
	else if (strcmp(directory, "-") == 0)
	{
		directory = getenv("OLDPWD");
		printf("%s\n", directory);
	}
	if (directory && chdir(directory) == -1)
		perror(directory);
	else
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", getcwd(NULL, 0), 1);
	}
}
