/*
** fork.c for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Fri Apr 10 01:37:32 2015 Matthieu SISCA
** Last update Sun Apr 12 22:47:13 2015 Paccard Christopher
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
#include "fork.h"

static void	set_name_comment_reg(t_champion *new_champ,
				     t_champion *champion)
{
  int		i;

  i = -1;
  while (champion->name[++i] != '\0')
    new_champ->name[i] = champion->name[i];
  new_champ->name[i] = '\0';
  i = -1;
  while (champion->comment[++i] != '\0')
    new_champ->comment[i] = champion->comment[i];
  new_champ->comment[i] = '\0';
  i = -1;
  while (++i <= REG_NUMBER)
    new_champ->reg[i] = champion->reg[i];
}

int		fork(t_champion *champion, unsigned char **arena)
{
  t_champion	*new_champ;
  char		tmp[4];

  if ((new_champ = my_malloc(sizeof(*new_champ))) == NULL)
    return (my_fprintf(2, "In \"fork,c\", malloc failed->"));
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  tmp[2] = (*arena)[(champion->pc) % MEM_SIZE];
  tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
  tmp[0] = 0;
  tmp[1] = 0;
  set_name_comment_reg(new_champ, champion);
  new_champ->size = champion->size;
  new_champ->number = champion->number;
  new_champ->address = champion->address;
  new_champ->code = champion->code;
  new_champ->live = champion->live;
  new_champ->is_waiting = champion->is_waiting;
  new_champ->wait_time = champion->wait_time;
  new_champ->carry = champion->carry;
  new_champ->next = champion->next;
  champion->next = new_champ;
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  new_champ->pc = champion->pc + ((SWAP_ENDIAN(*(int*)tmp)) % IDX_MOD);
  new_champ->pc %= MEM_SIZE;
  return (0);
}

int		lfork(t_champion *champion, unsigned char **arena)
{
  t_champion	*new_champ;
  char		tmp[4];

  if ((new_champ = my_malloc(sizeof(*new_champ))) == NULL)
    return (my_fprintf(2, "In \"fork,c\", malloc failed."));
  champion->pc = (champion->pc + 1) % MEM_SIZE;
  tmp[2] = (*arena)[(champion->pc) % MEM_SIZE];
  tmp[3] = (*arena)[(champion->pc + 1) % MEM_SIZE];
  tmp[0] = 0;
  tmp[1] = 0;
  set_name_comment_reg(new_champ, champion);
  new_champ->size = champion->size;
  new_champ->number = champion->number;
  new_champ->address = champion->address;
  new_champ->code = champion->code;
  new_champ->live = champion->live;
  new_champ->is_waiting = champion->is_waiting;
  new_champ->wait_time = champion->wait_time;
  new_champ->carry = champion->carry;
  new_champ->next = champion->next;
  champion->next = new_champ;
  champion->pc = (champion->pc + 2) % MEM_SIZE;
  new_champ->pc = (champion->pc + (SWAP_ENDIAN(*(int*)tmp))) % MEM_SIZE;
  return (0);
}
