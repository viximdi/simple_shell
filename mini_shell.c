#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.c"
#define MAX_COMMAND_LENGTH 100

/**
 * execute_command - Execute the given command using fork and execlp.
 * @command: The command to execute.
 */
void execute_command(const char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		execlp(command, command, NULL);
		perror(command);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}
