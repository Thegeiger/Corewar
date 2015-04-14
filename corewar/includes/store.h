/*
** store.h for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Thu Apr  9 20:11:24 2015 Matthieu SISCA
** Last update Sun Apr 12 21:30:12 2015 Paccard Christopher
*/

#ifndef STORE_H_
# define STORE_H_

# define PC_1 ((*arena)[(champion->pc + 1) % MEM_SIZE])
# define PC_3 ((*arena)[(champion->pc + 3) % MEM_SIZE])
# define PC_2 ((*arena)[(champion->pc + 2) % MEM_SIZE])

int	store(t_champion *champion, unsigned char **arena);

#endif /* !STORE_H_ */
