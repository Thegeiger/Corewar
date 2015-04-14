/*
** calcul.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:10:39 2015 Paccard Christopher
** Last update Sat Apr 11 23:34:48 2015 Matthieu SISCA
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
#include "calcul.h"

int	addition(t_champion *champion, unsigned char **arena)
{
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  if (((*arena)[(champion->pc + 1) % MEM_SIZE] <= REG_NUMBER) &&
      ((*arena)[(champion->pc + 2) % MEM_SIZE] <= REG_NUMBER) &&
      ((*arena)[(champion->pc + 3) % MEM_SIZE] <= REG_NUMBER))
    {
      REG_PC_3 = REG_PC_1 + REG_PC_2;
      if (REG_PC_3 != 0)
	champion->carry = 1;
    }
  else
	champion->carry = 0;
  champion->pc = (champion->pc + 4) % MEM_SIZE;
  return (0);
}

int	soustraction(t_champion *champion, unsigned char **arena)
{
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  if (((*arena)[(champion->pc + 1) % MEM_SIZE] <= REG_NUMBER) &&
      ((*arena)[(champion->pc + 2) % MEM_SIZE] <= REG_NUMBER) &&
      ((*arena)[(champion->pc + 3) % MEM_SIZE] <= REG_NUMBER))
    {
      REG_PC_3 = REG_PC_1 - REG_PC_2;
      if (REG_PC_3 != 0)
	champion->carry = 1;
    }
  else
    champion->carry = 0;
  champion->pc = (champion->pc + 4) % MEM_SIZE;
  return (0);
}
