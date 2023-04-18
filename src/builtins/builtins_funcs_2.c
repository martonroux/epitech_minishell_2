/*
** EPITECH PROJECT, 2023
** B-PSU
** File description:
** builtins_funcs_2.c
*/

#include "../../include/my.h"

void set_new_dir(list_struct *env_ll, char *new_dir)
{
    char cwd[PATH_MAX];
    char old_cwd[PATH_MAX];

    getcwd(old_cwd, sizeof(cwd));
    chdir(new_dir);
    getcwd(cwd, sizeof(cwd));
    setenv_function(env_ll, "PWD", cwd);
    setenv_function(env_ll, "OLDPWD", old_cwd);
    shell_var.exit_status = 0;
}

void cd_minus(list_struct *env_ll)
{
    char cwd[PATH_MAX];
    char *old_path;

    getcwd(cwd, sizeof(cwd));
    old_path = get_value_of_env_var(env_ll, "OLDPWD");
    if (my_str_comp(old_path, "") == true) {
        my_putstr_err(": No such file or directory.\n");
        shell_var.exit_status = 1;
        return;
    }
    chdir(old_path);
    setenv_function(env_ll, "PWD", old_path);
    setenv_function(env_ll, "OLDPWD", cwd);
}

void cd_function_bis(char const **arg, list_struct *env_ll)
{
    struct stat buf = {0};

    stat(arg[1], &buf);
    if (!S_ISDIR(buf.st_mode)) {
        my_putstr_err(arg[1]);
        my_putstr_err(": Not a directory.\n");
        shell_var.exit_status = 1;
        return;
    }
    set_new_dir(env_ll, (char *)arg[1]);
}

void cd_function(char const **arg, list_struct *env_ll)
{
    char *home_path;

    if (access(arg[1], F_OK) == -1) {
        home_path = get_value_of_env_var(env_ll, "HOME");
        if (arg[1] == NULL)
            return set_new_dir(env_ll, home_path);
        if (arg[1][0] == '-' && arg[1][1] == '\0')
            return cd_minus(env_ll);

        my_putstr_err(arg[1]);
        my_putstr_err(": No such file or directory.\n");
        shell_var.exit_status = 1;
        return;
    }
    return cd_function_bis(arg, env_ll);
}

void echo_function(list_struct *env_ll, char **args, char *PATH)
{
    if (args[1] != NULL) {
        if (args[1][0] == '$' && args[1][1] == '?') {
            my_putstr(my_int_to_str(shell_var.exit_status));
            my_putchar('\n');
            shell_var.exit_status = 0;
            return;
        }
    }
    execute_single_command(args, env_ll, PATH, 1);
}
