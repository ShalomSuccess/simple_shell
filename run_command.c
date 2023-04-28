#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * run- change directory
 * @file_: directory
 * @s_value: directory
 * @return an integer
 */
int run(const char *file_, int *s_value)
{
	FILE *fp = fopen(file_, "r");
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t read_line_value;
	char *dir;

		if (fp == NULL)
		{
			perror("Error opening file");
			return (EXIT_FAILURE);
		}
		while ((read_line_value = getline(&line, &bufsize, fp)) != -1)
		{
			if (line[read_line_value - 1] == '\n')
				line[read_line_value - 1] = '\0';
			if (strncmp(line, "cd ", 3) == 0)
			{
				dir = line + 3;
				change_dir(dir);
			}
			else if (strncmp(line, "setenv ", 7) == 0)
			{
				char *name = line + 7;
				char *value = strchr(name, ' ');

				if (value == NULL)
				{
					fprintf(stderr, "./%s: setenv: missing value\n", SHELL_NAME);
					continue;
				}
				*value++ = '\0';
				if (setenv(name, value, 1) == -1)
					perror("setenv");
			}
			else if (strncmp(line, "unsetenv ", 9) == 0)
			{
				char *name = line + 9;

				environ_unset_variable(name);
			}
			else
				execute_command(line);
		}
		fclose(fp);
		if (line)
			free(line);
		return (*s_value);
}
