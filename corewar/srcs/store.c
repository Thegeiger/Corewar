/*
** store.c for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Thu Apr  9 20:08:52 2015 Matthieu SISCA
** Last update Sun Apr 12 22:03:42 2015 Matthieu SISCA
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
#include "store.h"

int		store(t_champion *champion, unsigned char **arena)
{
  int		i;
  int		j;
  char		tmp[4];
  union u_int	value;

  j = 3;
  if ((IS_REGISTER(((*arena)[(champion->pc + 1) % MEM_SIZE]) << 2)) == 1)
    {
      if (PC_3 <= REG_NUMBER && PC_2 <= REG_NUMBER)
  	champion->reg[PC_3] = champion->reg[PC_2];
    }
  else
    {
      tmp[2] = (*arena)[(champion->pc + 3) % MEM_SIZE];
      tmp[3] = (*arena)[(champion->pc + 4) % MEM_SIZE];
      tmp[0] = 0;
      tmp[1] = 0;
      i = SWAP_ENDIAN(*(int*)tmp);
      if (PC_2 <= REG_NUMBER)
  	value.i = champion->reg[PC_2];
      while (j >= 0)
  	(*arena)[(champion->pc + 5 + (i++ % IDX_MOD)) % MEM_SIZE] = value.c[j--];
    }
  champion->pc += (((IS_REGISTER(PC_1 << 2)) == 1) ? 4 : 5) % MEM_SIZE;
  return (0);
}
