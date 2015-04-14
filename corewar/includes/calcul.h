/*
** calcul.h for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:05:29 2015 Paccard Christopher
** Last update Sun Apr 12 21:28:52 2015 Paccard Christopher
*/

#ifndef CALCUL_H_
# define CALCUL_H_

# define REG_PC_1 (champion->reg[(*arena)[(champion->pc + 1) % MEM_SIZE]])
# define REG_PC_2 (champion->reg[(*arena)[(champion->pc + 2) % MEM_SIZE]])
# define REG_PC_3 (champion->reg[(*arena)[(champion->pc + 3) % MEM_SIZE]])

int	addition(t_champion *champion, unsigned char **arena);
int	soustraction(t_champion *champion, unsigned char **arena);

#endif /* !CALCUL_H_ */
