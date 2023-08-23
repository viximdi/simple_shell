#ifndef SHELL_H
#define SHELL_H

typedef struct {
	char *key;
	char *value;
} EnvironmentVariable;

typedef struct {
	int fd;
	char buffer[BUFFER_SIZE];
	char *input_line;
} shell_data;

int read_input(shell_data *shell);
int process_logical_operators(char *command_queue[], int i, char operators_queue[]);
void clear_command_queue(char *command_queue[]);
void shift_queue(char queue[]);
int custom_exit_builtin(shell_info *shell);
int custom_change_directory(shell_info *shell);
int set_working_directory(shell_info *shell, char *new_dir);
int custom_help_builtin(shell_info *shell);
int custom_alias_builtin(shell_info *shell);
void execute_commands_from_file(const char *filename);
int display_custom_aliases(program_data *prog_data, char *alias_name);
char *get_custom_alias(program_data *prog_data, char *alias_name);
int set_custom_alias(char *alias_string, program_data *prog_data);
int perform_builtin(shell_program_data *shell_data);
void free_recurrent_data(data_of_program *data);
void free_all_data(data_of_program *data);
void free_array_of_pointers(char **array);
void convert_long_to_string(long num, char *str, int base);
int custom_atoi(char *s);
int count_chars(char *string, char character);
int custom_output(char *text);
int custom_output_error(char *text);
int print_custom_error(int error_code, custom_program_data *program_data);
int get_custom_strlen(char *str);
char *duplicate_custom_str(char *str);
int compare_custom_str(char *str1, char *str2, int num);
void run_shell(void);
void execute_command(const char *command);
char *concat_custom_str(char *str1, char *str2);
void reverse_custom_str(char *str);
int find_variable_index(char *key, EnvironmentVariable *variables, int size);
char *get_value_by_key(char *key, shell_data *shell_data);
int set_value_by_key(char *key, char *value, shell_data *shell_data);
int remove_key(char *key, shell_data *shell_data);
void print_environment(shell_data *shell_data);

size_t length = strlen(command);
void run_shell(void);
#endif
