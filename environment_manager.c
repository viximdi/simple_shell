#include "shell.h"

typedef struct {
	char *key;
	char *value;
} EnvironmentVariable;

/**
 * find_variable_index - Find the index of an environment variable by key.
 * @key: The key to search for.
 * @variables: Array of environment variables.
 * @size: Size of the variables array.
 * Return: Index of the variable if found, else -1.
 */
int find_variable_index(char *key, EnvironmentVariable *variables, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (str_compare(key, variables[i].key, 0))
		{
			return (i);
		}
	}
	return (-1);
}

/**
 * get_value_by_key - Retrieve the value of an environment variable by key.
 * @key: The key of the environment variable.
 * @shell_data: Pointer to the shell data struct.
 * Return: A pointer to the value or NULL if not found.
 */
char *get_value_by_key(char *key, shell_data *shell_data)
{
	if (key == NULL || shell_data->environment == NULL)
	{
		return (NULL);
	}

	int index = find_variable_index(key, shell_data->environment, shell_data->env_size);

	return ((index != -1) ? shell_data->environment[index].value : NULL;)
}

/**
 * set_value_by_key - Set or overwrite the value of an environment variable.
 * @key: The key of the variable to set.
 * @value: The new value for the variable.
 * @shell_data: Pointer to the shell data struct.
 * Return: 1 if parameters are NULL, 2 on error, or 0 on success.
 */
int set_value_by_key(char *key, char *value, shell_data *shell_data)
{
	if (key == NULL || value == NULL || shell_data->environment == NULL)
	{
		return (1);
	}

	int index = find_variable_index(key, shell_data->environment, shell_data->env_size);

	if (index != -1)
	{
		free(shell_data->environment[index].value);
		shell_data->environment[index].value = str_duplicate(value);
	}
	else
	{
		shell_data->environment = realloc(shell_data->environment,
				(shell_data->env_size + 1) * sizeof(EnvironmentVariable));
		shell_data->environment[shell_data->env_size].key = str_duplicate(key);
		shell_data->environment[shell_data->env_size].value = str_duplicate(value);
		shell_data->env_size++;
	}

	return (0);
}

/**
 * remove_key - Remove an environment variable by key.
 * @key: The key of the variable to remove.
 * @shell_data: Pointer to the shell data struct.
 * Return: 1 if the key was removed, 0 if the key doesn't exist.
 */
int remove_key(char *key, shell_data *shell_data)
{
	if (key == NULL || shell_data->environment == NULL)
	{
		return (0);
	}

	int index = find_variable_index(key, shell_data->environment, shell_data->env_size);

	if (index != -1)
	{
		free(shell_data->environment[index].key);
		free(shell_data->environment[index].value);
		for (int i = index; i < shell_data->env_size - 1; i++)
		{
			shell_data->environment[i] = shell_data->environment[i + 1];
		}
		shell_data->env_size--;
		shell_data->environment = realloc(shell_data->environment,
				shell_data->env_size * sizeof(EnvironmentVariable));
		return (1);
	}

	return (0);
}

/**
 * print_environment - Print the current environment variables.
 * @shell_data: Pointer to the shell data struct.
 * Return: None.
 */
void print_environment(shell_data *shell_data)
{
	for (int i = 0; i < shell_data->env_size; i++)
	{
		_custom_print(shell_data->environment[i].key);
		_custom_print("=");
		_custom_print(shell_data->environment[i].value);
		_custom_print("\n");
	}
}
