#include "shell.h"

/**
 * expandVariables - Expand variables
 * @data: A pointer to a struct of the program's data
 *
 * Return: Nothing, but sets errno.
 */
void expandVariables(data_of_program *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	bufferAdd(line, data->input_line);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			longToString(errno, expansion, 10);
			bufferAdd(line, expansion);
			bufferAdd(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			longToString(getpid(), expansion, 10);
			bufferAdd(line, expansion);
			bufferAdd(line, data->input_line + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expansion[j - 1] = line[i + j];
			temp = envGetKey(expansion, data);
			line[i] = '\0', expansion[0] = '\0';
			bufferAdd(expansion, line + i + j);
			temp ? bufferAdd(line, temp) : 1;
			bufferAdd(line, expansion);
		}
	if (!strCompare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = strDuplicate(line);
	}
}

/**
 * expandAlias - Expand aliases
 * @data: A pointer to a struct of the program's data
 *
 * Return: Nothing, but sets errno.
 */
void expandAlias(data_of_program *data)
{
	int i, j, wasExpanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	bufferAdd(line, data->input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expansion[j] = line[i + j];
		expansion[j] = '\0';

		temp = getAlias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			bufferAdd(expansion, line + i + j);
			line[i] = '\0';
			bufferAdd(line, temp);
			line[strLength(line)] = '\0';
			bufferAdd(line, expansion);
			wasExpanded = 1;
		}
		break;
	}
	if (wasExpanded)
	{
		free(data->input_line);
		data->input_line = strDuplicate(line);
	}
}

/**
 * bufferAdd - Append string at end of the buffer
 * @buffer: Buffer to be filled
 * @strToAdd: String to be copied in the buffer
 * Return: Nothing, but sets errno.
 */
int bufferAdd(char *buffer, char *strToAdd)
{
	int length, i;

	length = strLength(buffer);
	for (i = 0; strToAdd[i]; i++)
	{
		buffer[length + i] = strToAdd[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
