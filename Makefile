##
## Makefile for Corewar in /home/paccar_c/rendu/CPE_2014_corewar
## 
## Made by Paccard Christopher
## Login   <paccar_c@epitech.net>
## 
## Started on  Wed Apr  8 23:49:46 2015 Paccard Christopher
## Last update Sat Apr 11 16:51:06 2015 anthony geiger
##

NAME	 = Corewar

all: 	 $(NAME)

$(NAME): asm corewar

asm:
	 make -C asm

corewar:
	 make -C corewar

clean_asm:
	 make clean -C asm

clean_corewar:
	 make clean -C corewar

re_asm:
	 make re -C asm

re_corewar:
	 make re -C corewar
fclean_asm:
	 make fclean -C asm

fclean_corewar:
	 make fclean -C corewar

clean:
	 make clean -C asm
	 make clean -C corewar

fclean:  
	 make fclean -C asm
	 make fclean -C corewar

re:	 fclean all

.PHONY:  all clean fclean re clean_asm clean_corewar asm corewar fclean_corewar fclean_asm re_asm re_corewar
