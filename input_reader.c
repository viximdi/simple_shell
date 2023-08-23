#include "shell.h"

#define MAX_COMMANDS 10

/**
 * read_input - read input lines from the prompt and handle logical operators
 * @shell: shell data struct
 * Return: length of input line, or -1 on EOF
 */
int read_input(shell_data *shell)
{
	static char *command_queue[MAX_COMMANDS] = {NULL};
	static char operators_queue[MAX_COMMANDS] = {'\0'};
	ssize_t bytes_read;
	size_t i = 0;

	if (!command_queue[0] || (operators_queue[0] == '&' && errno != 0) ||
			(operators_queue[0] == '|' && errno == 0))
	{
		clear_command_queue(command_queue);
		bytes_read = read(shell->fd, shell->buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		i = 0;
		do {
			command_queue[i] = custom_strtok(i ? NULL : shell->buffer, "\n;");
			i = process_logical_operators(command_queue, i, operators_queue);
		} while (command_queue[i++]);
	}

	shell->input_line = command_queue[0];
	shift_queue(command_queue);
	shift_queue(operators_queue);

	return (custom_strlen(shell->input_line));
}

/**
 * process_logical_operators - split input line on && and || operators
 * @command_queue: array of commands
 * @i: current index in command_queue
 * @operators_queue: array of logical operators for each previous command
 * Return: index of the last command in command_queue
 */
int process_logical_operators(char *command_queue[], int i, char operators_queue[])
{
	char *temp = NULL;
	int j;

	for (j = 0; command_queue[i] != NULL && command_queue[i][j]; j++)
	{
		if (command_queue[i][j] == '&' && command_queue[i][j + 1] == '&')
		{
			temp = command_queue[i];
			command_queue[i][j] = '\0';
			command_queue[i] = custom_strduplicate(command_queue[i]);
			command_queue[i + 1] = custom_strduplicate(temp + j + 2);
			i++;
			operators_queue[i] = '&';
			custom_free(temp);
			j = 0;
		}
		if (command_queue[i][j] == '|' && command_queue[i][j + 1] == '|')
		{
			temp = command_queue[i];
			command_queue[i][j] = '\0';
			command_queue[i] = custom_strduplicate(command_queue[i]);
			command_queue[i + 1] = custom_strduplicate(temp + j + 2);
			i++;
			operators_queue[i] = '|';
			custom_free(temp);
			j = 0;
		}
	}
	return (i);
}

/**
 * clear_command_queue - free memory and clear command queue
 * @command_queue: array of commands
 */
void clear_command_queue(char *command_queue[])
{
	for (size_t i = 0; command_queue[i]; i++)
	{
		custom_free(command_queue[i]);
		command_queue[i] = NULL;
	}
}

/**
 * shift_queue - shift elements in the queue left by one position
 * @queue: array to shift
 */
void shift_queue(char queue[])
{
	for (size_t i = 0; queue[i]; i++)
	{
		queue[i] = queue[i + 1];
	}
}
