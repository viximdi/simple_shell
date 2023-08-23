#include "shell.h"

/**
 * release_recurring_data - Releases the fields required per loop iteration
 * @data: Pointer to the program's data struct
 * Return: Nothing
 */
void release_recurring_data(data_of_program *data)
{
	if (data->tokens)
		free_pointer_array(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->command_name)
		free(data->command_name);

	data->input_line = NULL;
	data->command_name = NULL;
	data->tokens = NULL;
}

/**
 * release_all_data - Releases all fields of the data struct
 * @data: Pointer to the program's data struct
 * Return: Nothing
 */
void release_all_data(data_of_program *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	release_recurring_data(data);
	free_pointer_array(data->env);
	free_pointer_array(data->alias_list);
}

/**
 * free_pointer_array - Frees each element of an array of pointers and the array itself
 * @array: Array of pointers
 * Return: Nothing
 */
void free_pointer_array(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
