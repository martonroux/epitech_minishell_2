##
## EPITECH PROJECT, 2022
## Project
## File description:
## makefile.c
##

CFLAGS = -W -Wall -Wextra -g3

SRC = main.c \
	$(wildcard src/*.c) \
	$(wildcard src/builtins/*.c) \
	$(wildcard src/my_functions/*.c) \
	$(wildcard src/take_command/*.c) \
	$(wildcard src/free/*.c) \
	$(wildcard src/error_gest/*.c)
OBJ = $(SRC:.c=.o)

TARGET_RUN = mysh

$(TARGET_RUN) : $(OBJ)
	$(CC) -o $@ $(OBJ) -Iinclude

all : $(TARGET_RUN) clean

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(TARGET_RUN)

re : fclean all
	$(RM) $(OBJ)
