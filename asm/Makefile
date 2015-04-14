##
## Makefile for Corewar in /home/paccar_c/rendu/corewar/asm
## 
## Made by Paccard Christopher
## Login   <paccar_c@epitech.net>
## 
## Started on  Mon Mar 23 00:17:00 2015 Paccard Christopher
## Last update Sun Apr 12 11:58:20 2015 Paccard Christopher
##

CC		= gcc

NAME		= asm

SRCS_DIR_LIB	= ../lib/srcs/

SRCS_LIB	= string.c \
		  string_compare.c \
		  nbr.c \
		  malloc_gen_list.c \
		  string_copy.c \
		  my_malloc.c \
		  get_next_line.c \
		  my_fprintf.c \
		  op.c

OBJS_LIB	= $(addprefix $(SRCS_DIR_LIB), $(SRCS_LIB:.c=.o))

SRCS_DIR	= srcs/

SRCS		= main.c \
		  gen_list.c \
		  check_param.c \
		  compil.c \
		  get_argv.c \
		  lexer.c \
		  process.c \
		  write_argvs.c \
		  write_header.c \
		  label.c

OBJS		= $(addprefix $(SRCS_DIR), $(SRCS:.c=.o))

CFLAGS		= -Wall -Wextra -Werror -ansi -pedantic -I./includes -I./../lib/includes/

all: 	 $(NAME)

$(NAME): $(OBJS_LIB) $(OBJS)
	 $(CC) $(OBJS_LIB) $(OBJS) -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJS_LIB) $(OBJS)

fclean: clean
	rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re
