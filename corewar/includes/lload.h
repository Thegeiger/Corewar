/*
** lload.h for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Thu Apr  9 20:22:44 2015 Matthieu SISCA
** Last update Sun Apr 12 21:28:05 2015 Paccard Christopher
*/

#ifndef LLOAD_H_
# define LLOAD_H_

# define PC_IND_SIZE ((champion->pc + IND_SIZE + 2) % MEM_SIZE)
# define PC_DIR_SIZE ((champion->pc + DIR_SIZE) % MEM_SIZE)

int	lload(t_champion *champion, unsigned char **arena);

#endif /* !LLOAD_H_ */
