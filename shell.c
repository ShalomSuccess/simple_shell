#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * main - main entry to code
 * @argc: the name of the environment variable to unset
 * @argv: the name of the environment variable to unset
 * @return 0 on success, -1 on failure
 */
int main(int argc, char *argv[])
{
    
    int shell_command = isatty(STDIN_FILENO);
    int status = 0;
	char *line = NULL;
    size_t bufsize = 0;
    ssize_t read_line_variable;

    if (argc == 2)
    {
		int stat = run(argv[1], &status);
		return (stat);
    }

    while (1)
    {
        if (shell_command)
            printf("($) ");
        read_line_variable = getline(&line, &bufsize, stdin);
        if (read_line_variable == -1)
            break;
        if (line[read_line_variable - 1] == '\n')
            line[read_line_variable - 1] = '\0';
        if (strcmp(line, "exit") == 0)
        {
            exit(status);
        }
        else if (strncmp(line, "exit ", 5) == 0)
        {
            char *code_str = line + 5;
            status = atoi(code_str);
            exit(status);
        }
        else if (strncmp(line, "cd ", 3) == 0)
        {
            char *dir = line + 3;
            change_dir(dir);
        }
        else if (strncmp(line, "setenv ", 7) == 0)
        {
            char *name = line + 7;
            char *value = strchr(name, ' ');
            if (value == NULL)
            {
                fprintf(stderr, "./hsh: setenv: missing value\n");
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

    if (line)
        free(line);
    exit(status);
}
