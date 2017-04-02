##
## Makefile for tetris in /home/cheval_8/rendu/PSU_2015_tetris
##
## Made by Chevalier Nicolas
## Login   <cheval_8@epitech.net>
##
## Started on  Wed Feb 24 16:02:04 2016 Chevalier Nicolas
## Last update Sun Apr  2 23:44:08 2017 Boris ROUGAGNOU
##

CC		= gcc

NAME		= lemipc

SRC		= srcs/main.c \
		  srcs/check.c \
		  srcs/move.c \
		  srcs/lock.c \
		  srcs/ia.c \
		  srcs/init.c \
		  srcs/usage.c \
		  srcs/display.c \
		  srcs/choose.c

OBJ		= $(SRC:.c=.o)

CFLAGS	= 	-W -Wall -Wextra -I./includes

RM		= rm -f

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
