##
## Makefile for tetris in /home/cheval_8/rendu/PSU_2015_tetris
##
## Made by Chevalier Nicolas
## Login   <cheval_8@epitech.net>
##
## Started on  Wed Feb 24 16:02:04 2016 Chevalier Nicolas
## Last update Fri May 27 22:52:50 2016 Nicolas Chevalier
##


NAME		=	lemipc

SRC		= 	srcs/main.c

MOD		=	$(SRC:.c=.o)

CFLAGS		=	-Iincludes/


all:		$(NAME)

$(NAME):	$(MOD)
		@cc $(MOD) -o $(NAME)

clean		:
		 rm -rf $(MOD)

fclean		: clean
		  rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
