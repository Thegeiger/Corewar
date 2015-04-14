/*
** load.h for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:07:17 2015 Paccard Christopher
** Last update Sun Apr 12 21:28:09 2015 Paccard Christopher
*/

#ifndef LOAD_H_
# define LOAD_H_

# define PC_IND_SIZE ((champion->pc + IND_SIZE + 2) % MEM_SIZE)
# define PC_DIR_SIZE ((champion->pc + DIR_SIZE) % MEM_SIZE)

int	load(t_champion *champion, unsigned char **arena);

#endif /* !LOAD_H_ */
