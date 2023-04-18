/*
** EPITECH PROJECT, 2023
** B_PSU
** File description:
** main.c
*/

#include "../include/my.h"

list_struct *ll_initialize(void)
{
    list_struct *list = malloc(sizeof(list_struct));

    list->first = NULL;
    return list;
}

void ll_add_first(list_struct *head, char *value)
{
    node *new_node = malloc(sizeof(node));

    new_node->value = value;
    new_node->next = head->first;
    new_node->previous = NULL;

    if (head->first != NULL)
        head->first->previous = new_node;
    head->first = new_node;
}

void ll_add_last(list_struct *head, char *value)
{
    node *new_node = malloc(sizeof(node));
    node *actual = head->first;

    if (head->first == NULL)
        return ll_add_first(head, value);
    new_node->value = value;
    while (actual->next != NULL)
        actual = actual->next;
    new_node->next = NULL;
    new_node->previous = actual;
    actual->next = new_node;
}

void ll_delete(list_struct *head, node *to_del)
{
    if (head->first == NULL || to_del == NULL)
        return;

    if (to_del == head->first)
        head->first = to_del->next;

    if (to_del->next != NULL)
        to_del->next->previous = to_del->previous;

    if (to_del->previous != NULL)
        to_del->previous->next = to_del->next;
}

void ll_print(list_struct *head)
{
    node *actual = head->first;

    while (actual != NULL) {
        my_putstr(actual->value);
        my_putchar('\n');
        actual = actual->next;
    }
}
