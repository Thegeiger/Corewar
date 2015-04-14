/*
** corewar.h for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:05:43 2015 Paccard Christopher
** Last update Sun Apr 12 21:31:00 2015 Paccard Christopher
*/

#ifndef COREWAR_H_
# define COREWAR_H_

# include "champion.h"

# define IS_REGISTER(char) (((char) & (0xC0)) == (0x40) ? (1) : (0))
# define IS_DIRECT(char) (((char) & (0xC0)) == (0x80) ? (1) : (0))
# define IS_INDIRECT(char) (((char) & (0xC0)) == (0xC0) ? (1) : (0))

union	u_int
{
  int	i;
  char	c[4];
};

typedef struct	s_corewar
{
  int		dump;
  int		nbr_champions;
  int		team_live[4];
  t_champion	*champions;
}		t_corewar;

#endif /* !COREWAR_H_ */
