/*
** lldi.c for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Fri Apr 10 01:38:00 2015 Matthieu SISCA
** Last update Sun Apr 12 22:38:10 2015 Paccard Christopher
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
#include "ldi.h"

static int	lldi_direct_indirect(t_champion *champion,
				     unsigned char **arena, char codage)
{
  char		tmp[4];
  int		i;

  champion->pc = (champion->pc + 1) % MEM_SIZE;
  tmp[2] = (*arena)[champion->pc];
  tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
  tmp[1] = 0;
  tmp[0] = 0;
  i = SWAP_ENDIAN(*(int*)tmp);
  if ((IS_INDIRECT(codage)) == 1)
    {
      if ((IS_REGISTER(codage << 2)) == 1)
	{
	  tmp[2] = (*arena)[(champion->pc + 4 + i) % MEM_SIZE];
	  tmp[3] = (*arena)[(champion->pc + 5 + i) % MEM_SIZE];
	}
      else
	{
	  tmp[2] = (*arena)[(champion->pc + 5 + i) % MEM_SIZE];
	  tmp[3] = (*arena)[(champion->pc + 6 + i) % MEM_SIZE];
	}
      i = SWAP_ENDIAN(*(int*)tmp);
    }
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  return (my_sec_arg(champion, arena, codage, i));
}

static int	lput_in_reg(t_champion *champion, unsigned char **arena, int i)
{
  int		j;
  char		tmp[4];

  j = 0;
  if ((*arena)[champion->pc] <= REG_NUMBER)
    {
      while (j < 4)
	tmp[j++] = (*arena)[(champion->pc + i++) % MEM_SIZE];
      champion->reg[(*arena)[champion->pc]] = SWAP_ENDIAN(*(int*)tmp);
      if (champion->reg[(*arena)[champion->pc]] != 0)
	champion->carry = 1;
    }
  else
    champion->carry = 0;
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  return (0);
}

int	lldi(t_champion *champion, unsigned char **arena)
{
  char	codage;
  int	i;

  champion->pc = (champion->pc + 1) % MEM_SIZE;
  codage = (*arena)[champion->pc];
  if ((IS_REGISTER(codage)) == 1)
    i = ldi_reg(champion, arena, codage);
  else
    i = lldi_direct_indirect(champion, arena, codage);
  lput_in_reg(champion, arena, i);
  return (0);
}
