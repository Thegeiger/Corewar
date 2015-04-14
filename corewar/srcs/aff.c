/*
** aff.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:08:08 2015 Paccard Christopher
** Last update Sun Apr 12 19:08:23 2015 Matthieu SISCA
*/

#include <stdlib.h>
#include <unistd.h>
#include "corewar.h"
#include "champion.h"
#include "string_compare.h"
#include "string.h"
#include "nbr.h"
#include "my_fprintf.h"
#include "my_malloc.h"
#include "gen_list.h"
#include "vm.h"

int	my_aff(t_champion *champion, unsigned char **arena)
{
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  if ((*arena)[champion->pc] <= REG_NUMBER)
    my_putchar(champion->reg[(*arena)[champion->pc]] % 256);
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  return (0);
}
