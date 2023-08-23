#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/**
 * customGetLine - Custom implementation of getline
 *
 * Return: A dynamically allocated line read from stdin, or NULL on EOF/error
 */
char *customGetLine(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t buffer_position = 0;
	static ssize_t buffer_size = 0;

	char *line = NULL;
	size_t line_length = 0;

	while (1)
	{
		if (buffer_position >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			buffer_position = 0;

			if (buffer_size <= 0)
			{
				if (line_length == 0)
				{
					return (NULL);
				}
				else
				{
					break;
				}
			}
		}

		char c = buffer[buffer_position++];
		if (c == '\n')
		{
			break;
		}

		if (line_length % BUFFER_SIZE == 0)
		{
			size_t new_length = line_length + BUFFER_SIZE;
			line = realloc(line, new_length);
			if (!line)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}
		line[line_length++] = c;
	}

	if (line)
	{
		line[line_length] = '\0';
	}

	return (line);
}
