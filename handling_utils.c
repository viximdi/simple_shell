#include "shell.h"

/**
 * custom_output - writes an array of characters to the standard output
 * @text: pointer to the array of characters
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_output(char *text)
{
	return (write(STDOUT_FILENO, text, custom_strlen(text)));
}

/**
 * custom_output_error - writes an array of characters to the standard error
 * @text: pointer to the array of characters
 * Return: the number of bytes written
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_output_error(char *text)
{
	return (write(STDERR_FILENO, text, custom_strlen(text)));
}

/**
 * print_custom_error - prints an error message to the standard error
 * @error_code: error code to print
 * @program_data: a pointer to the program's data
 * Return: 0 on success
 */
int print_custom_error(int error_code, custom_program_data *program_data)
{
	char counter_as_string[10] = {'\0'};

	custom_long_to_string((long) program_data->execution_count, counter_as_string, 10);

	if (error_code == 2 || error_code == 3)
	{
		custom_output_error(program_data->program_name);
		custom_output_error(": ");
		custom_output_error(counter_as_string);
		custom_output_error(": ");
		custom_output_error(program_data->tokens[0]);
		if (error_code == 2)
			custom_output_error(": Invalid number: ");
		else
			custom_output_error(": Can't change directory to ");
		custom_output_error(program_data->tokens[1]);
		custom_output_error("\n");
	}
	else if (error_code == 127)
	{
		custom_output_error(program_data->program_name);
		custom_output_error(": ");
		custom_output_error(counter_as_string);
		custom_output_error(": ");
		custom_output_error(program_data->command_name);
		custom_output_error(": not found\n");
	}
	else if (error_code == 126)
	{
		custom_output_error(program_data->program_name);
		custom_output_error(": ");
		custom_output_error(counter_as_string);
		custom_output_error(": ");
		custom_output_error(program_data->command_name);
		custom_output_error(": Permission denied\n");
	}
	return (0);
}
