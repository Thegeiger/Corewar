/*
** live.h for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:00:56 2015 Paccard Christopher
** Last update Sun Apr 12 21:31:04 2015 Paccard Christopher
*/

#ifndef LIVE_H_
# define LIVE_H_

# define NO_NUMBER ("There is no champion with number %i\n")
# define ALREADY_DEAD ("Player %s says \"live\" but was dead\n")

int	check_live(t_corewar *corewar, int *nbr_winner);
int	live(t_champion *champion, int *backup_cycles,
	     unsigned char **arena, t_corewar *corewar);

#endif /* !LIVE_H_ */
