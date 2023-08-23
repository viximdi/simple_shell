#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

/**
 * run_shell - Run a simple shell program that executes
 * commands with arguments.
 */
void run_shell(void)
{
	char input[100];
	char *args[20];
	int arg_count = 0;
	char *token;

	while (1)
	{
		printf("Enter a command: ");
		fgets(input, sizeof(input), stdin);

		input[strcspn(input, "\n")] = 0;

		*token = strtok(input, " ");
		arg_count = 0;
		while (token != NULL)
		{
			args[arg_count] = token;
			arg_count++;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		pid_t pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execvp(args[0], args);
			perror("Exec failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
}
