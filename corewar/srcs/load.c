/*
** load.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:45:14 2015 Paccard Christopher
** Last update Sun Apr 12 22:37:46 2015 Paccard Christopher
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
#include "load.h"

static int	load_indirect(t_champion *champion, unsigned char **arena)
{
  int		i;
  int		j;
  char		tmp[4];

  j = 4;
  tmp[2] = (*arena)[(champion->pc + 2) % MEM_SIZE];
  tmp[3] = (*arena)[(champion->pc + 3) % MEM_SIZE];
  tmp[0] = 0;
  tmp[1] = 0;
  i = SWAP_ENDIAN(*(int*)tmp);
  while (--j >= 0)
    tmp[j] = (*arena)[(champion->pc + 5 + (i++ % IDX_MOD)) % MEM_SIZE];
  if ((*arena)[(champion->pc + IND_SIZE + 2) % MEM_SIZE] <= REG_NUMBER)
    {
      champion->reg[(*arena)[PC_IND_SIZE]] = (*(int*)tmp);
      if (champion->reg[(*arena)[PC_IND_SIZE]] != 0)
  	champion->carry = 1;
    }
  else
    champion->carry = 0;
  champion->pc = (champion->pc + IND_SIZE + 3) % MEM_SIZE;
  return (0);
}

int	load(t_champion *champion, unsigned char **arena)
{
  int	i;
  char	tmp[4];

  i = -1;
  if ((IS_DIRECT(((*arena)[(champion->pc + 1) % MEM_SIZE]))) == 1)
    {
      champion->pc = champion->pc + 2 % MEM_SIZE;
      while (i++ < 4)
	tmp[i] = (*arena)[(champion->pc + i) % MEM_SIZE];
      if ((*arena)[(champion->pc + IND_SIZE + 2) % MEM_SIZE] <= REG_NUMBER)
	champion->reg[(*arena)[PC_DIR_SIZE]] = SWAP_ENDIAN(*(int*)tmp);
      if (((*arena)[(champion->pc + IND_SIZE + 2) % MEM_SIZE] <= REG_NUMBER) &&
	  champion->reg[(*arena)[PC_DIR_SIZE]] != 0)
	champion->carry = 1;
      else
	champion->carry = 0;
      champion->pc = (champion->pc + DIR_SIZE + 1) % MEM_SIZE;
    }
  else if ((IS_INDIRECT((*arena)[(champion->pc + 1) % MEM_SIZE])) == 1)
    load_indirect(champion, arena);
  return (0);
}
