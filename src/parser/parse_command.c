/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** parse_command
*/

#include "my.h"
#include "shell.h"
#include "my_list.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **line_to_array(char const *str);
void extend_array(char ***array, char *new_line);
void execute_command(sh_data_t *data);
command_t *malloc_command(void);
int handle_io_output(sh_data_t *data, char **options, bool *error);
int handle_io_output_append(sh_data_t *data, char **options, bool *error);
int handle_io_input(sh_data_t *data, char **options, bool *error);
int handle_io_input_line(sh_data_t *data, char **options, bool *error);
int handle_io_pipe(sh_data_t *data, char **options, bool *error);
int retrieve_io(sh_data_t *data);
void close_current_pipe(sh_data_t *data);
void close_other_pipe(sh_data_t *data);
void reset_data(sh_data_t *data);
int handle_separators(sh_data_t *data, char **options, bool *error,
                        const special_token_t *token_list);
int check_if_separator(char *str);
special_token_t get_io_token(const special_token_t *token_list, char *str);
char *remove_quote(char *str);
char *init_str(int size);
int handle_args(sh_data_t *data, char *str, int *i);
int var_substitute(sh_data_t *data);
int alias_handler(sh_data_t *data);
void handle_backtick(sh_data_t *data);
char *handle_ascii_inhib(char *str);
char *history_maker(char **line, int length, int len, char *clock);
char *history_make(char **line, int length, int len);
char *command_time();
void init_command_execution(sh_data_t *data);

static const special_token_t TOKEN_LIST[] = {
    {">>", 2, &handle_io_output_append},
    {">", 1, &handle_io_output},
    {"<<", 2, &handle_io_input_line},
    {"<", 1, &handle_io_input},
    {"|", 1, &handle_io_pipe},
    {NULL, 0, NULL}
};

static void fill_command_args(sh_data_t *data, char *str, int *i, bool *error)
{
    char *tmp = init_str(my_strlen(str));
    my_strcpy(tmp, str);
    str = remove_quote(str);
    if (my_strcmp(tmp, str) != 0) {
        str = handle_ascii_inhib(str);
        extend_array(&data->current_command->argv, str);
        data->current_command->argc++;
        *i = *i + 1;
        return;
    }
    if (!handle_args(data, str, i))
        *error = true;
}

static int parse_next_command(sh_data_t *data, char **line, bool *error)
{
    int i = 0;
    special_token_t io_token;
    data->current_command = malloc_command();
    while (line[i] != NULL) {
        if (check_if_separator(line[i]))
            return i;
        io_token = get_io_token(TOKEN_LIST, line[i]);
        if (io_token.size == 0) {
            fill_command_args(data, line[i], &i, error);
            continue;
        }
        line[i + 1] = remove_quote(line[i + 1]);
        i += io_token.handler(data, &line[i + 1], error);
    }
    return (i + 1);
}

static void parse_command_and_exec(sh_data_t *data, int len)
{
    bool error = false;
    for (int i = 0; i < len ;) {
        if (check_if_separator(data->line[i])) {
            i += handle_separators(data, &data->line[i], &error, TOKEN_LIST);
            continue;
        }
        i += parse_next_command(data, &data->line[i], &error);
        if (!error)
            init_command_execution(data);
        else {
            error = false;
            data->last_exit_status = 1;
        }
    }
}

static void second_parser(sh_data_t *data)
{
    int len = 0;
    int length = 0;
    char status[10];
    char *time = command_time();
    char *last_command = my_strdup("");
    int backtick_status = data->last_exit_status;
    for (; data->line[len] != NULL; len++)
        for (int i = 0; data->line[len][i] != '\0'; i++, length++);
    length += len + 1;
    length += my_strlen(time);
    data->history_index++;
    last_command = history_maker(data->line, length, len, time);
    extend_array(&data->history, last_command);
    parse_command_and_exec(data, len);
    data->last_exit_status = data->last_exit_status == 0 ? backtick_status :
        data->last_exit_status;
    sprintf(status, "%d", data->last_exit_status);
    set_var_value(data, "status", status);
}

void parse_current_line(sh_data_t *data, char *line)
{
    data->last_exit_status = 0;
    line[my_strlen(line) - 1] = line[my_strlen(line) - 1] == '\n' ?
        '\0' : line[my_strlen(line) - 1];
    data->line = line_to_array(line);
    if (data->line == NULL || data->line[0] == NULL) {
        data->last_exit_status = 1;
        return;
    }
    alias_handler(data);
    handle_backtick(data);
    if (var_substitute(data)) {
        data->last_exit_status = 1;
        return;
    }
    second_parser(data);
}
