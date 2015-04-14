/*
** operation.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:55:59 2015 Paccard Christopher
** Last update Sun Apr 12 22:05:10 2015 Matthieu SISCA
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

static void	set_indirect(t_champion *champion, int *nb,
			     unsigned char **arena)
{
  int		i;
  int		j;
  char		tmp[4];

  i = 0;
  j = 0;
  while (i < 4)
    tmp[i++] = 0;
  tmp[2] = (*arena)[(champion->pc) % MEM_SIZE];
  tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
  i = SWAP_ENDIAN(*(int*)tmp);
  while (j < 4)
    tmp[j++] = (*arena)[(champion->pc + (i++ % IDX_MOD)) % MEM_SIZE];
  *nb = SWAP_ENDIAN(*(int*)tmp);
  champion->pc = (champion->pc + 2) % MEM_SIZE;
}

static void	get_nb(t_champion *champion, unsigned char **arena,
		       int *nb, char codage)
{
  int		i;
  char		tmp[4];

  i = -1;
  if (IS_DIRECT(codage) == 1)
    {
      while (i++ < 4)
	tmp[i] = (*arena)[(champion->pc + i) % MEM_SIZE];
      *nb = SWAP_ENDIAN(*(int*)tmp);
      champion->pc = (champion->pc + DIR_SIZE) % MEM_SIZE;
    }
  else if (IS_INDIRECT(codage) == 1)
    set_indirect(champion, nb, arena);
  else if (IS_REGISTER(codage) == 1)
    {
      if (((*arena)[champion->pc]) <= REG_NUMBER)
	*nb = champion->reg[(*arena)[champion->pc]];
      champion->pc = (champion->pc + 1) % MEM_SIZE;
    }
}

int	my_and(t_champion *champion, unsigned char **arena)
{
  int	nb1;
  int	nb2;
  char	codage;

  nb1 = 0;
  nb2 = 0;
  codage = (*arena)[(champion->pc + 1) % MEM_SIZE];
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  get_nb(champion, arena, &nb1, codage);
  get_nb(champion, arena, &nb2, codage << 2);
  if (((*arena)[champion->pc]) <= REG_NUMBER)
    {
      champion->reg[(*arena)[champion->pc]] = nb1 & nb2;
      if ((champion->reg[(*arena)[champion->pc]] != 0))
	champion->carry = 1;
    }
  else
    champion->carry = 0;
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  return (0);
}

int	my_or(t_champion *champion, unsigned char **arena)
{
  int	nb1;
  int	nb2;
  char	codage;

  nb1 = 0;
  nb2 = 0;
  codage = (*arena)[(champion->pc + 1) % MEM_SIZE];
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  get_nb(champion, arena, &nb1, codage);
  get_nb(champion, arena, &nb2, codage << 2);
  if (((*arena)[champion->pc]) <= REG_NUMBER)
    {
      champion->reg[(*arena)[champion->pc]] = nb1 | nb2;
      if (champion->reg[(*arena)[champion->pc]] != 0)
	champion->carry = 1;
    }
  else
    champion->carry = 0;
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  return (0);
}

int	my_xor(t_champion *champion, unsigned char **arena)
{
  int	nb1;
  int	nb2;
  char	codage;

  nb1 = 0;
  nb2 = 0;
  codage = (*arena)[(champion->pc + 1) % MEM_SIZE];
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  get_nb(champion, arena, &nb1, codage);
  get_nb(champion, arena, &nb2, codage << 2);
  if (((*arena)[champion->pc]) <= REG_NUMBER)
    {
      champion->reg[(*arena)[champion->pc]] = nb1 ^ nb2;
      if (champion->reg[(*arena)[champion->pc]] != 0)
	champion->carry = 1;
    }
  else
    champion->carry = 0;
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  return (0);
}
