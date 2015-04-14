/*
** vm.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:47:08 2015 Paccard Christopher
** Last update Sun Apr 12 22:36:42 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "corewar.h"
#include "champion.h"
#include "string_compare.h"
#include "nbr.h"
#include "my_fprintf.h"
#include "my_malloc.h"
#include "gen_list.h"
#include "vm.h"
#include "the_game.h"

static int	check()
{
  if (IND_SIZE != 2)
    return (my_fprintf(2, "In \"op.h\", please set IND_SIZE = 2"));
  if (REG_SIZE != 4)
    return (my_fprintf(2, "In \"op.h\", please set REG_SIZE = 4"));
  if (DIR_SIZE != REG_SIZE)
    return (my_fprintf(2, "In \"op.h\", please set DIR_SIZE = REG_SIZE"));
  if (CYCLE_TO_DIE <= 0)
    return (my_fprintf(2, "In \"op.h\", CYCLE_TO_DIE must be positive"));
  if (CYCLE_DELTA <= 0)
    return (my_fprintf(2, "In \"op.h\", CYCLE_DELTA must be positive"));
  if (CYCLE_DELTA >= CYCLE_TO_DIE)
    return (my_fprintf(2, "In \"op.h\", CYCLE_DELTA > CYCLE_TO_DIE"));
  if (NBR_LIVE <= 0)
    return (my_fprintf(2, "In \"op.h\", NBR_LIVE must be positive"));
  return (0);
}

static void	set_empty(t_corewar *corewar, unsigned char **arena)
{
  int		i;
  t_champion	*tmp;

  i = 0;
  tmp = corewar->champions;
  while (i < MEM_SIZE)
    (*arena)[i++] = 0;
  while (tmp)
    {
      i = 0;
      tmp->carry = 0;
      tmp->wait_time = 0;
      tmp->live = 0;
      while (i <= REG_NUMBER)
	tmp->reg[i++] = 0;
      tmp->reg[1] = tmp->number;
      tmp = tmp->next;
    }
}

static int	set_arena(t_corewar *corewar, unsigned char **arena)
{
  int		i;
  int		index;
  t_champion	*tmp;

  tmp = corewar->champions;
  if ((*arena = my_malloc(MEM_SIZE * sizeof(char))) == NULL)
    return (my_fprintf(2, "At set_arena : Malloc failed.\n"));
  set_empty(corewar, arena);
  i = 0;
  while (tmp)
    {
      index = tmp->address;
      tmp->pc = index;
      while ((tmp->code) && (i < tmp->size) && (index < MEM_SIZE))
	if ((*arena)[index] == 0)
	  (*arena)[(index++) % MEM_SIZE] = tmp->code[i++];
	else
	  return (my_fprintf(2, "In \"set_arena\", address conflict\n"));
      i = 0;
      tmp = tmp->next;
    }
  return (0);
}

int		my_vm(t_corewar *corewar)
{
  unsigned char	*arena;
  int		cycles;
  int		backup_cycles;
  int		i;

  i = 0;
  while (i < 4)
    {
      corewar->team_live[i] = 0;
      ++i;
    }
  cycles = CYCLE_TO_DIE;
  backup_cycles = cycles;
  if (check())
    return (-1);
  if (set_arena(corewar, &arena))
    return (my_fprintf(2, "In my_vm.\n"));
  lets_play(corewar, cycles, backup_cycles, &arena);
  return (0);
}
