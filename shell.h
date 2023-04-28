#ifndef SHELL_H
#define SHELL_H

#define SHELL_NAME "hsh"

void change_dir(char *dir);
void environ_unset_variable(char *name);
void execute_command(char *line);
int run(const char *file_, int *s_value);

#endif
