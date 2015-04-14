##
## Makefile for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar
## 
## Made by Paccard Christopher
## Login   <paccar_c@epitech.net>
## 
## Started on  Thu Apr  9 08:55:56 2015 Paccard Christopher
## Last update Sun Apr 12 23:26:56 2015 Matthieu SISCA
##

CC		= gcc

NAME		= corewar

SRCS_DIR_LIB	= ../lib/srcs/

SRCS_LIB	= string.c		\
		  string_compare.c	\
		  nbr.c			\
		  my_fprintf.c		\
		  my_malloc.c		\
		  malloc_gen_list.c	\
		  get_next_line.c	\
		  op.c

OBJS_LIB	= $(addprefix $(SRCS_DIR_LIB), $(SRCS_LIB:.c=.o))

SRCS_DIR	= srcs/

SRCS		= main.c	\
		  champion.c	\
		  vm.c		\
		  the_game.c	\
		  live.c	\
		  load.c	\
		  store.c	\
		  calcul.c	\
		  operation.c	\
		  zjump.c	\
		  lload.c	\
		  sti.c		\
		  ldi.c		\
		  fork.c	\
		  lldi.c	\
		  aff.c

OBJS		= $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

CFLAGS		= -I./includes/ -I../lib/includes/
CFLAGS		+= -Wall -Wextra -Werror -ansi -pedantic


all: 		$(NAME)

$(NAME): 	$(OBJS_LIB) $(OBJS)
		$(CC) $(OBJS_LIB) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
		rm -f $(OBJS_LIB) $(OBJS)

fclean: 	clean
		rm -f $(NAME)

re:		fclean all

.PHONY: 	all clean fclean re
