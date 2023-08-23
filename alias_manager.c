#include "shell.h"

int display_custom_aliases(program_data *prog_data, char *alias_name)
{
	int i, j, alias_name_length;
	char output_buffer[250] = {'\0'};

	if (prog_data->custom_aliases)
	{
		alias_name_length = str_length(alias_name);
		for (i = 0; prog_data->custom_aliases[i]; i++)
		{
			if (!alias_name || (str_compare(prog_data->custom_aliases[i], alias_name, alias_name_length)
						&&	prog_data->custom_aliases[i][alias_name_length] == '='))
			{
				for (j = 0; prog_data->custom_aliases[i][j]; j++)
				{
					output_buffer[j] = prog_data->custom_aliases[i][j];
					if (prog_data->custom_aliases[i][j] == '=')
						break;
				}
				output_buffer[j + 1] = '\0';
				buffer_append(output_buffer, "'");
				buffer_append(output_buffer, prog_data->custom_aliases[i] + j + 1);
				buffer_append(output_buffer, "'\n");
				_custom_print(output_buffer);
			}
		}
	}

	return (0);
}

char *get_custom_alias(program_data *prog_data, char *alias_name)
{
	int i, alias_name_length;

	if (alias_name == NULL || prog_data->custom_aliases == NULL)
		return (NULL);

	alias_name_length = str_length(alias_name);

	for (i = 0; prog_data->custom_aliases[i]; i++)
	{
		if (str_compare(alias_name, prog_data->custom_aliases[i], alias_name_length) &&
				prog_data->custom_aliases[i][alias_name_length] == '=')
		{
			return (prog_data->custom_aliases[i] + alias_name_length + 1);
		}
	}

	return (NULL);
}

int set_custom_alias(char *alias_string, program_data *prog_data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  prog_data->custom_aliases == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
	{
		if (alias_string[i] != '=')
		{
			buffer[i] = alias_string[i];
		}
		else
		{
			temp = get_custom_alias(prog_data, alias_string + i + 1);
			break;
		}
	}

	for (j = 0; prog_data->custom_aliases[j]; j++)
	{
		if (str_compare(buffer, prog_data->custom_aliases[j], i) &&
				prog_data->custom_aliases[j][i] == '=')
		{
			free(prog_data->custom_aliases[j]);
			break;
		}
	}

	if (temp)
	{
		buffer_append(buffer, "=");
		buffer_append(buffer, temp);
		prog_data->custom_aliases[j] = str_duplicate(buffer);
	}
	else
	{
		prog_data->custom_aliases[j] = str_duplicate(alias_string);
	}

	return (0);
}
