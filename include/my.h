/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** my.h
*/

#pragma once

#define CD 0
#define SETENV 1
#define UNSETENV 2
#define ENV 3
#define EXIT 4
#define ECHO 5
#define WIFCORED(s) ((s) & 0200)

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <linux/limits.h>
#include <errno.h>
#include <signal.h>
#include "shell_var.h"

typedef enum func_s {
    NONE = 0,
    SEPARATOR = 1,
    PIPE = 2,
    SIMPLE_REDIRECT_RIGHT = 3,
    SIMPLE_REDIRECT_LEFT = 4,
    COMPLEX_REDIRECT_RIGHT = 5,
    COMPLEX_REDIRECT_LEFT = 6
} func_t;

extern shell_var_t shell_var;

typedef struct element_t node;

struct element_t {
    char *value;
    node *next;
    node *previous;
};

typedef struct list_t {
    node *first;
} list_struct;

typedef struct exec_data_s {
    char **arg;
    list_struct *env_ll;
    char *PATH;
    int skip_builtin;
} exec_data_t;

void my_putstr(char const *str);
void my_putstr_err(char const *str);
void take_command(list_struct *env_ll, char *PATH);
char **get_args(char *argv);
int my_strlen(char const *str);
char *concat_str(char const *str1, char const *str2);
char **args_without_newline(char *argv);
char *get_path(char *command, char *PATH);
int compare_strings(char const *str1, char const *str2);
void cd_function(char const **arg, list_struct *env_ll);
void execute_builtins(
    char const *command,
    char const **arg,
    list_struct *env_ll,
    char *PATH
    );
int check_builtin(char const *command);
void exit_function(char **arg);
void my_putchar(char c);
void env_function(list_struct *env_ll);
list_struct *ll_initialize(void);
void ll_add_first(list_struct *head, char *value);
void ll_add_last(list_struct *head, char *value);
void ll_delete(list_struct *head, node *to_del);
void ll_print(list_struct *head);
list_struct *env_to_ll(char **env);
char *my_str_cat(char *str1, char *str2);
node *get_env_param(list_struct *head, char *name);
void setenv_function(
    list_struct *env_ll,
    char *name,
    char *value
    );
int my_str_to_int(char *str);
int my_array_len(char **arr);
bool is_alpha_num(char c);
bool is_alpha(char c);
int setenv_error_gest(char **args, list_struct *env_ll);
void unsetenv_function(list_struct *env_ll, char **args);
char *get_path_bis(char *command);
char *get_value_of_env_var(list_struct *env_ll, char *name);
char *my_int_to_str(int nb);
void echo_function(list_struct *env_ll, char **args, char *PATH);
void execute_single_command(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    );
int exec_separator(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    );
bool my_str_comp(char *str1, char *str2);
bool is_in_array(char **array, char *sep);
char **env_ll_to_array(list_struct *env_ll);
char **get_arg_until_sep(char **arg, char *sep);
void free_char_array(char **array);
int exec_sr_rl(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    );
func_t check_if_func(char *arg);
char **get_arg_redirect(char **arg, char *sep);
char *get_file_name_redirect(char **arg, char *sep);
void open_pipe(void);
void close_pipe(void);
int exec_cr_rl(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    );
int exec_sr_lr(
    char **arg,
    list_struct *env_ll,
    char *PATH,
    int skip_builtin
    );
bool my_str_contains(char *str, char *contains);
void error_gest_fork(int status, char *command);
void error_gest_fork_crash(char *command);
bool char_is_in_str(char *str, char c);
func_t char_is_func(char arg);
bool is_simple_char(char c, int skip_space_tabs);
char *local_to_malloc_word(char word[4096]);
void print_unmatched(int had_char);
int change_had_char(int had_char, char c, int *had_quotes);
int exec_pipe(exec_data_t exec_data);
int nb_pipes(char **arg);
int len_pipe_arg(char **arg);
char **get_last_command(char **arg);
void dup_all(int in_fd, int fd[2]);
int get_next_len_func(char *argv);
int get_next_len_normal(char *argv);
bool check_if_int(char *str);
