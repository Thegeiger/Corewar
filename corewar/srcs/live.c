/*
** live.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:42:00 2015 Paccard Christopher
** Last update Sun Apr 12 23:03:15 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "op.h"
#include "corewar.h"
#include "champion.h"
#include "string_compare.h"
#include "nbr.h"
#include "my_fprintf.h"
#include "my_malloc.h"
#include "gen_list.h"
#include "live.h"
#include "vm.h"

static void	reset_live(t_corewar *corewar)
{
  t_champion	*tmp;
  int		i;

  i = 0;
  while (i < 4)
    {
      if (corewar->team_live[i] == 1)
	corewar->team_live[i] = 0;
      i = i + 1;
    }
  tmp = corewar->champions;
  while (tmp)
    {
      if (tmp->live == 1)
	tmp->live = 0;
      tmp = tmp->next;
    }
}

int		check_live(t_corewar *corewar, int *nbr_winner)
{
  int		dead;
  int		i;
  t_champion	*tmp;

  tmp = corewar->champions;
  dead = 0;
  while (tmp)
    {
      tmp->live = (tmp->live == 0 ? -1 : tmp->live);
      tmp = tmp->next;
    }
  i = -1;
  while (++i < corewar->nbr_champions)
    {
      if (corewar->team_live[i] == 0 || corewar->team_live[i] == -1)
	{
	  ++dead;
	  if (corewar->team_live[i] == 0)
	    my_fprintf(1, "Player %i is dead :(\n", i);
	  corewar->team_live[i] = -1;
	}
      *nbr_winner = (corewar->team_live[i] == 1 ? i : *nbr_winner);
    }
  reset_live(corewar);
  return ((((corewar->nbr_champions - dead) <= 1) ? -1 : dead));
}

static void	check_cycles(int *live,
			     int *backup_cycles, t_corewar *corewar)
{
  static int	decrement = 1;
  int		nb_dead;
  int		nbr_winner;

  nbr_winner = -1;
  *live = *live + 1;
  if (*live == 40)
    {
      *live = 0;
      if ((nb_dead = check_live(corewar, &nbr_winner)) == -1)
	{
	  my_fprintf(1, "Player %i won :)\n", nbr_winner);
	  *backup_cycles = 0;
	}
      else if (nb_dead > 0)
	return ;
      else if (nb_dead == 0)
	{
	  *backup_cycles = CYCLE_TO_DIE - (decrement++ * CYCLE_DELTA);
	  if (*backup_cycles < 0)
	    *backup_cycles = 0;
	}
    }
}

static int	is_alive(t_champion *champion, int nb, int *backup_cycles,
			 t_corewar *corewar)
{
  static int	live = 0;
  t_champion	*tmp;

  tmp = champion;
  if (0 <= nb && nb < corewar->nbr_champions && corewar->team_live[nb] != -1)
    {
      if (corewar->team_live[nb] == -1)
	return (my_fprintf(2, ALREADY_DEAD, tmp->name));
      corewar->team_live[nb] = 1;
      my_fprintf(1, "Player %i %s is alive\n", tmp->number, tmp->name);
    }
  else
    return (my_fprintf(2, "", nb));
  if (nb == tmp->number && corewar->team_live[nb] != -1)
    tmp->live = 1;
  check_cycles(&live, backup_cycles, corewar);
  return (0);
}

int	live(t_champion *champion, int *backup_cycles, unsigned char **arena,
	     t_corewar *corewar)
{
  int	number;
  char	tmp[4];

  number = -1;
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  while (++number < 4)
    tmp[number] = (*arena)[(champion->pc + number) % MEM_SIZE];
  number = SWAP_ENDIAN(*(int*)tmp);
  is_alive(champion, number, backup_cycles, corewar);
  champion->pc = (champion->pc + DIR_SIZE) % MEM_SIZE;
  return (0);
}
