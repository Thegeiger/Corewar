/*
** the_game.c for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Fri Apr 10 16:32:34 2015 Matthieu SISCA
** Last update Sun Apr 12 23:02:38 2015 Paccard Christopher
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
#include "vm.h"
#include "aff.h"
#include "calcul.h"
#include "fork.h"
#include "ldi.h"
#include "live.h"
#include "lldi.h"
#include "lload.h"
#include "load.h"
#include "operation.h"
#include "sti.h"
#include "store.h"
#include "zjump.h"
#include "the_game.h"
#include "vm.h"

static int	(*g_fct[])(t_champion*, unsigned char**) =
{
  &load,
  &store,
  &addition,
  &soustraction,
  &my_and,
  &my_or,
  &my_xor,
  &zjump,
  &ldi,
  &sti,
  &fork,
  &lload,
  &lldi,
  &lfork,
  &my_aff
};

static void	my_action(int *backup_cycles, unsigned char **arena,
			  t_corewar *corewar, t_champion *tmp)
{
  if (PC_OP_CODE == -1)
    live(tmp, backup_cycles, arena, corewar);
  else if (0 <= PC_OP_CODE && PC_OP_CODE <= 15)
    {
      g_fct[PC_OP_CODE](tmp, arena);
      tmp->is_waiting = 0;
    }
  else
    tmp->pc = (tmp->pc + 1) % MEM_SIZE;
}

static int	your_turn(int *backup_cycles,
			  unsigned char **arena, t_corewar *corewar)
{
  t_champion	*tmp;

  tmp = corewar->champions;
  while (tmp)
    {
      if (tmp->live != -1)
	{
	  if (tmp->is_waiting == 0 && 0 <= (PC_OP_CODE + 2) &&
	      (PC_OP_CODE + 2) < 16)
	    {
	      tmp->wait_time = op_tab[PC_OP_CODE + 2].nbr_cycles;
	      tmp->is_waiting = 1;
	    }
	  if (tmp->wait_time == 0)
	    my_action(backup_cycles, arena, corewar, tmp);
	  else
	    tmp->wait_time--;
	}
      tmp = tmp->next;
    }
  return (0);
}

static void	dump_it(t_corewar *corewar, unsigned char **arena)
{
  int		i;

  i = 0;
  if (corewar->dump != -1)
    {
      while (i < MEM_SIZE)
	{
	  my_fprintf(1, "%x ", (*arena)[i]);
	  i = i + 1;
	  if ((i % 32) == 0 && i != 0)
	    my_fprintf(1, "\n");
        }
    }
}

int	lets_play(t_corewar *corewar, int cycles, int backup_cycles,
		  unsigned char **arena)
{
  int	nbr_winner;

  nbr_winner = -1;
  while (backup_cycles > 0 && cycles != (CYCLE_TO_DIE - corewar->dump))
    {
      if (cycles == 0)
	{
	  cycles = backup_cycles;
	  if (check_live(corewar, &nbr_winner) == -1)
	    {
	      if (nbr_winner != -1)
		my_fprintf(1, "Player %i won :)\n", nbr_winner);
	      else
		my_fprintf(1, "No player won :/\n");
	      return (0);
	    }
	}
      your_turn(&backup_cycles, arena, corewar);
      cycles = cycles - 1;
    }
  if (corewar->dump != -1)
    dump_it(corewar, arena);
  return (0);
}
