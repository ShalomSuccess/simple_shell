#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: exits with a given exit status
 *         (0) if info.arguments[0] != "exit"
 */
int exit_shell(info_t *info)
{
	int exit_status;

	if (info->arguments[1])  /* If there is an exit argument */
	{
		exit_status = convert_to_integer(info->arguments[1]);
		if (exit_status == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->arguments[1]);
			_eputchar('\n');
			return (1);
		}
		info->error_num = convert_to_integer(info->arguments[1]);
		return (-2);
	}
	info->error_num = -1;
	return (-2);
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int change_directory(info_t *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arguments[1])
	{
		dir = get_environment_variable(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = get_environment_variable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->arguments[1], "-") == 0)
	{
		if (!get_environment_variable(info, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(get_environment_variable(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_environment_variable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->arguments[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->arguments[1]), _eputchar('\n');
	}
	else
	{
		set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
		set_environment_variable(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * display_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->arguments;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
