/*
** zjump.c for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Thu Apr  9 18:40:35 2015 Matthieu SISCA
** Last update Sun Apr 12 18:29:51 2015 Matthieu SISCA
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

int	zjump(t_champion *champion, unsigned char **arena)
{
  char	tmp[4];
  int	i;

  tmp[0] = 0;
  tmp[1] = 0;
  if (champion->carry == 1)
    {
      tmp[2] = (*arena)[(champion->pc + 1) % MEM_SIZE];
      tmp[3] = (*arena)[(champion->pc + 2) % MEM_SIZE];
      i = SWAP_ENDIAN(*(int*)tmp);
      champion->pc = (champion->pc + 3 + (i % IDX_MOD)) % MEM_SIZE;
    }
  else
    champion->pc = (champion->pc + 3) % MEM_SIZE;
  return (0);
}
