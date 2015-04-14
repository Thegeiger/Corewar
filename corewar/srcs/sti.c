/*
** sti.c for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Fri Apr 10 01:02:24 2015 Matthieu SISCA
** Last update Sun Apr 12 22:06:33 2015 Matthieu SISCA
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

static int	my_thirg_arg(t_champion *champion, unsigned char **arena,
			     char codage)
{
  char		tmp[4];
  int		i;

  tmp[0] = 0;
  tmp[1] = 0;
  if ((IS_REGISTER((codage << 4))) == 1)
    {
      if ((*arena)[champion->pc] <= REG_NUMBER)
	i = champion->reg[(*arena)[champion->pc]];
      champion->pc = (champion->pc + 1) % MEM_SIZE;
    }
  else if ((IS_DIRECT((codage << 2))) == 1)
    {
      tmp[2] = (*arena)[champion->pc];
      tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
      i = SWAP_ENDIAN(*(int*)tmp);
      champion->pc = (champion->pc + 2) % MEM_SIZE;
    }
  return (i);
}

static int	my_ind(t_champion *champion, unsigned char **arena, char codage)
{
  int		i;
  int		j;
  char		tmp[4];

  j = 4;
  tmp[2] = (*arena)[champion->pc];
  tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
  tmp[0] = 0;
  tmp[1] = 0;
  i = SWAP_ENDIAN(*(int*)tmp);
  i = i + ((IS_REGISTER(codage << 4)) == 1 ? 3 : 4);
  while (--j >= 0)
    tmp[j] = (*arena)[(champion->pc + (i++ % IDX_MOD)) % MEM_SIZE];
  i = (*(int*)tmp);
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  return (i);
}

static int	get_second_arg(t_champion *champion, unsigned char **arena,
			       char codage)
{
  int		i;
  char		tmp[4];

  tmp[0] = 0;
  tmp[1] = 0;
  if ((IS_REGISTER((codage << 2))) == 1)
    {
      if ((*arena)[champion->pc] <= REG_NUMBER)
	i = champion->reg[(*arena)[champion->pc]];
      champion->pc = (champion->pc + 1) % MEM_SIZE;
    }
  else if ((IS_DIRECT((codage << 2))) == 1)
	{
	  tmp[2] = (*arena)[champion->pc];
	  tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
	  i = SWAP_ENDIAN(*(int*)tmp);
	  champion->pc = (champion->pc + 2) % MEM_SIZE;
	}
  else if ((IS_INDIRECT((codage << 2))) == 1)
    i = my_ind(champion, arena, codage);
  return (i);
}

int		sti(t_champion *champion, unsigned char **arena)
{
  char		codage;
  int		i;
  union u_int	value;

  champion->reg[2] = 4660;

  codage = (*arena)[(champion->pc + 1) % MEM_SIZE];
  if ((*arena)[(champion->pc + 2) % MEM_SIZE] <= REG_NUMBER)
    value.i = champion->reg[(*arena)[(champion->pc + 2) % MEM_SIZE]];
  champion->pc = (champion->pc + 3) % MEM_SIZE;
  i = get_second_arg(champion, arena, codage);
  i = i + my_thirg_arg(champion, arena, codage);
  (*arena)[(champion->pc + i) % MEM_SIZE] = value.c[3];
  (*arena)[(champion->pc + i + 1) % MEM_SIZE] = value.c[2];
  (*arena)[(champion->pc + i + 2) % MEM_SIZE] = value.c[1];
  (*arena)[(champion->pc + i + 3) % MEM_SIZE] = value.c[0];
  return (0);
}
