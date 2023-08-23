#include "shell.h"
/**
 * custom_exit_builtin - Exit the program with a status code.
 * @shell: Pointer to the shell_info struct.
 * Return: Returns the exit status.
 */
int custom_exit_builtin(shell_info *shell)
{
	int i;

	if (shell->args[1] != NULL)
	{
		for (i = 0; shell->args[1][i]; i++)
			if ((shell->args[1][i] < '0' || shell->args[1][i] > '9')
					&& shell->args[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = custom_atoi(shell->args[1]);
	}
	custom_free_data(shell);
	exit(errno);
}

/**
 * custom_change_directory - Change the current working directory.
 * @shell: Pointer to the shell_info struct.
 * Return: Returns 0 on success, an error code otherwise.
 */

int custom_change_directory(shell_info *shell)
{
	char *home_dir = custom_get_env("HOME", shell);
	char *old_dir = NULL;
	char prev_dir[128] = {0};
	int error_code = 0;

	if (shell->args[1])
	{
		if (custom_compare_strings(shell->args[1], "-", 0))
		{
			old_dir = custom_get_env("OLDPWD", shell);
			if (old_dir)
				error_code = set_working_directory(shell, old_dir);
			custom_print(custom_get_env("PWD", shell));
			custom_print("\n");
			return (error_code);
		}
		else
		{
			return (set_working_directory(shell, shell->args[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = custom_getcwd(prev_dir, 128);

		return (set_working_directory(shell, home_dir));
	}
	return (0);
}

/**
 * set_working_directory - Set the current working directory.
 * @shell: Pointer to the shell_info struct.
 * @new_dir: Path to be set as the working directory.
 * Return: Returns 0 on success, an error code otherwise.
 */

int set_working_directory(shell_info *shell, char *new_dir)
{
	char prev_dir[128] = {0};
	int err_code = 0;

	custom_getcwd(prev_dir, 128);

	if (!custom_compare_strings(prev_dir, new_dir, 0))
	{
		err_code = custom_chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		custom_set_env("PWD", new_dir, shell);
	}
	custom_set_env("OLDPWD", prev_dir, shell);
	return (0);
}

/**
 * custom_help_builtin - Display help messages for built-in commands.
 * @shell: Pointer to the shell_info struct.
 * Return: Returns 0 on success, an error code otherwise.
 */

int custom_help_builtin(shell_info *shell)
{
	int i, length = 0;
	char *messages[6] = {NULL};

	messages[0] = HELP_MESSAGE;

	if (shell->args[1] == NULL)
	{
		custom_print(messages[0] + 6);
		return (1);
	}
	if (shell->args[2] != NULL)
	{
		errno = E2BIG;
		perror(shell->command_name);
		return (5);
	}
	messages[1] = HELP_EXIT_MESSAGE;
	messages[2] = HELP_ENV_MESSAGE;
	messages[3] = HELP_SETENV_MESSAGE;
	messages[4] = HELP_UNSETENV_MESSAGE;
	messages[5] = HELP_CHANGE_DIR_MESSAGE;

	for (i = 0; messages[i]; i++)
	{
		length = custom_strlen(shell->args[1]);
		if (custom_compare_strings(shell->args[1], messages[i], length))
		{
			custom_print(messages[i] + length + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(shell->command_name);
	return (0);
}

/**
 * custom_alias_builtin - Manage shell aliases.
 * @shell: Pointer to the shell_info struct.
 * Return: Returns 0 on success, an error code otherwise.
 */

int custom_alias_builtin(shell_info *shell)
{
	int i = 0;

	if (shell->args[1] == NULL)
		return (custom_print_aliases(shell, NULL));

	while (shell->args[++i])
	{
		if (count_chars(shell->args[i], "="))
			set_alias(shell->args[i], shell);
		else
			custom_print_aliases(shell, shell->args[i]);
	}

	return (0);
}
