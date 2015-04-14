/*
** champion.h for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:01:34 2015 Paccard Christopher
** Last update Sun Apr 12 21:40:17 2015 Paccard Christopher
*/

#ifndef CHAMPION_H_
# define CHAMPION_H_

# include "op.h"

# define LEFT(nbr) (((nbr>>24) & 0xff) | ((nbr<<8) & 0xff0000))
# define RIGHT(nbr) (((nbr>>8) & 0xff00) | ((nbr<<24) & 0xff000000))
# define SWAP_ENDIAN(nbr) (LEFT(nbr) | RIGHT(nbr))

typedef struct		s_champion
{
  char			name[PROG_NAME_LENGTH + 1];
  int			size;
  char			comment[COMMENT_LENGTH + 1];
  int			number;
  int			address;
  unsigned char		*code;
  int			live;
  int			pc;
  int			is_waiting;
  int			wait_time;
  int			reg[REG_NUMBER + 1];
  int			carry;
  struct s_champion	*next;
}			t_champion;

int	my_champion(int argc, char **argv, int *i, t_champion *champion);

#endif /* !CHAMPION_H_ */
