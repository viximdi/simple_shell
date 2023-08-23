#include "shell.h"

/**
 * main - Initialize the shell and run the main loop
 * @argc: Number of values received from the command line
 * @argv: Values received from the command line
 * @env: Environment variables received from the command line
 * Return: 0 on success
 */
int main(int argc, char *argv[], char *env[])
{
	shell_data shell;
	char *prompt = "";

	initialize_shell_data(&shell, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	run_shell(prompt, &shell);
	return 0;
}

/**
 * handle_ctrl_c - Handle the SIGINT signal (Ctrl+C) by printing a new line and the prompt
 * @signum: The signal number
 */
void handle_ctrl_c(int signum)
{
	(void) signum;
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_shell_data - Initialize the shell data structure
 * @shell: Pointer to the shell_data structure
 * @argc: Number of values received from the command line
 * @argv: Values received from the command line
 * @env: Environment variables received from the command line
 */
void initialize_shell_data(shell_data *shell, int argc, char *argv[], char **env)
{
	int i = 0;

	shell->program_name = argv[0];
	shell->input_line = NULL;
	shell->command_name = NULL;
	shell->exec_counter = 0;

	if (argc == 1)
	{
		shell->file_descriptor = STDIN_FILENO;
	}
	else
	{
		shell->file_descriptor = open(argv[1], O_RDONLY);
		if (shell->file_descriptor == -1)
		{
			_printe(shell->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}

	shell->tokens = NULL;
	shell->environment = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			shell->environment[i] = str_duplicate(env[i]);
		}
	}
	shell->environment[i] = NULL;

	initialize_custom_alias_list(shell);
	initialize_environment_variables(shell);
}

/**
 * run_shell - Run the main shell loop
 * @prompt: The shell prompt
 * @shell: Pointer to the shell_data structure
 */
void run_shell(char *prompt, shell_data *shell)
{
	int error_code = 0, string_len = 0;

	while (++(shell->exec_counter))
	{
		_print(prompt);
		error_code = string_len = _getline(shell);

		if (error_code == EOF)
		{
			free_all_data(shell);
			exit(errno);
		}
		if (string_len >= 1)
		{
			expand_custom_aliases(shell);
			expand_environment_variables(shell);
			tokenize_input(shell);
			if (shell->tokens[0])
			{
				error_code = execute_command(shell);
				if (error_code != 0)
				{
					_print_error(error_code, shell);
				}
			}
			free_recurrent_data(shell);
		}
	}
}
