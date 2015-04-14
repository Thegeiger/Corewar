/*
** the_game.h for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 08:59:04 2015 Paccard Christopher
** Last update Sun Apr 12 21:27:27 2015 Paccard Christopher
*/

#ifndef THE_GAME_H_
# define THE_GAME_H_

# define PC_OP_CODE (((*arena)[tmp->pc] - 2))

int	lets_play(t_corewar *corewar, int cycles,
		  int backup_cycles, unsigned char **arena);

#endif /* !THE_GAME_H_ */
