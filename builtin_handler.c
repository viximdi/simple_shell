#include "shell.h"

/**
 * perform_builtin - Search for a matching builtin and execute it
 * @shell_data: Data structure for the shell program
 * Return: Returns the return value of the executed function if there's a match,
 * otherwise returns -1.
 **/

int perform_builtin(shell_program_data *shell_data)
{
	int index;
	builtin_info available_commands[] = {
		{"exit_cmd", builtin_exit_cmd},
		{"assist_cmd", builtin_assist_cmd},
		{"change_dir_cmd", builtin_change_dir_cmd},
		{"define_alias_cmd", builtin_define_alias_cmd},
		{"environment_cmd", builtin_environment_cmd},
		{"set_variable_cmd", builtin_set_variable_cmd},
		{"unset_variable_cmd", builtin_unset_variable_cmd},
		{NULL, NULL}
	};

	for (index = 0; available_commands[index].cmd_name != NULL; index++)
	{
		if (compare_cmd_names(available_commands[index].cmd_name, shell_data->command_name, 0))
		{
			return (available_commands[index].cmd_handler(shell_data));
		}
	}

	return (-1);
}
