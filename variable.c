#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * environ_unset_variable- change directory
 * @var: directory
 * @return void
 */
void environ_unset_variable(char *var)
{
	if (unsetenv(var) == -1)
		perror("unsetenv");
}
