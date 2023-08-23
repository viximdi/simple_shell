#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.c"
#define MAX_COMMAND_LENGTH 100

/**
 * execute_commands_from_file - Execute commands from a file.
 * @filename: The name of the file containing commands.
 *
 * This function reads commands from the specified file and executes each
 * command using the system() function.
 */
void execute_commands_from_file(const char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	char command[MAX_COMMAND_LENGTH];
	while (fgets(command, sizeof(command), file) != NULL)
	{
		command[strcspn(command, "\n")] = '\0';

		int result = system(command);
		if (result == -1)
		{
			perror("Error executing command");
		}
	}

	fclose(file);
}
