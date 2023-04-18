/*
** EPITECH PROJECT, 2023
** B-PSU
** File description:
** my_functions_6.c
*/

#include "../../include/my.h"

int my_nb_len(int nb)
{
    int len = 0;

    if (nb < 0)
        nb = -nb;
    do {
        nb /= 10;
        len++;
    } while (nb > 0);
    return len;
}

char *my_int_to_str(int nb)
{
    int i = 0;
    int nb_len = (nb < 0) ? my_nb_len(nb) + 1 : my_nb_len(nb);
    char *result = malloc(sizeof(char) * (nb_len + 1));
    result[nb_len] = '\0';

    if (nb < 0) {
        result[0] = '-';
        nb = -nb;
        i++;
    }
    if (nb == 0)
        result[i] = '0';
    for (i = nb_len - 1; nb > 0; i--) {
        result[i] = nb % 10 + '0';
        nb /= 10;
    }
    return result;
}

bool check_if_int(char *str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
