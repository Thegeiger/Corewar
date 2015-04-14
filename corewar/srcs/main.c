/*
** main.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:54:02 2015 Paccard Christopher
** Last update Sun Apr 12 22:22:53 2015 Matthieu SISCA
*/

#include <unistd.h>
#include "corewar.h"
#include "vm.h"
#include "string_compare.h"
#include "nbr.h"
#include "my_fprintf.h"
#include "my_malloc.h"
#include "gen_list.h"

/*
** brief: set the champion's address for each champion depending total of champions and parameters
** @corewar: our structure for the virtual machine
** return: void
*/
static void	my_champion_adress(t_corewar *corewar)
{
  t_champion	*champion_tmp;
  unsigned int	gap;
  unsigned int	address;

  champion_tmp = corewar->champions;
  gap = MEM_SIZE / corewar->nbr_champions;
  address = 0;
  while (champion_tmp)
    {
      if (champion_tmp->address == 0)
	champion_tmp->address = address;
      champion_tmp->address %= MEM_SIZE;
      address += gap;
      champion_tmp = champion_tmp->next;
    }
}

/*
** brief: set the champion in the correct position on the list depending his number
** @corewar: our structure for the virtual machine
** @champion: our structure for each champion
** return: {0 if succeed} {1 if number already taken}
*/
static unsigned int	my_order_champion(t_corewar *corewar,
					  t_champion *champion)
{
  t_champion		*champion_tmp;

  champion_tmp = corewar->champions;
  while (champion_tmp && champion_tmp->next)
    {
      if (champion_tmp->number == champion->number)
	return (my_fprintf(2, "number \"%i\" already used\n", champion->number));
      champion_tmp = champion_tmp->next;
    }
  if (!corewar->champions || corewar->champions->number > champion->number)
    {
      champion->next = corewar->champions;
      corewar->champions = champion;
    }
  else if (corewar->champions->number < champion->number)
    {
      champion_tmp->next = champion;
      champion_tmp->next->next = NULL;
    }
  else
    return (my_fprintf(2, "prog number %i already used.\n", champion->number));
  ++corewar->nbr_champions;
  return (0);
}

/*
** brief: get all the parameters for the virtual machine
** @argc: number of arguments pass to the program
** @argv: each arguments pass to the program
** @corewar: our structure for the virtual machine
** return: {0 if succeed} {1 if error during parsing}
*/
static unsigned int	my_get_params(int argc, char **argv, t_corewar *corewar)
{
  t_champion		*champion;
  int			i;

  i = 1;
  if (!my_strcmp(argv[i], "-dump"))
    {
      if (i + 1 >= argc || my_str_isnum(argv[i + 1]) ||
	  (corewar->dump = my_getnbr(argv[i + 1])) < 0)
	return (my_fprintf(2, "Dump must have a positive number.\n"));
      i += 2;
    }
  else
    corewar->dump = -1;
  while (i < argc)
    {
      if (!(champion = my_malloc(sizeof(*champion))))
	return (my_fprintf(2, "At my_get_params : Malloc failed.\n"));
      if (my_champion(argc, argv, &i, champion))
	return (1);
      if (my_order_champion(corewar, champion))
	return (1);
    }
  return (0);
}

/*
** brief: launch the differents functions for the virtual machine
** @argc: number of arguments pass to the program
** @argv: each arguments pass to the program
** return: {0 if succeed} {1 if anything went wrong}
*/
int		main(int argc, char **argv)
{
  t_corewar	corewar;

  if (argc == 1)
    {
      my_fprintf(2, "Usage: corewar [-dump nbr_cycle] [[-n ");
      my_fprintf(2, "prog_number] [-a load_address ] prog_name] ...\n");
      return (1);
    }
  corewar.champions = NULL;
  corewar.nbr_champions = 0;
  if (my_get_params(argc, argv, &corewar))
    {
      my_free();
      return (1);
    }
  if (corewar.nbr_champions < 1 || corewar.nbr_champions > MAX_ARGS_NUMBER)
    {
      my_free();
      return (my_fprintf(2, "You need 1 to %i champions.\n", MAX_ARGS_NUMBER));
    }
  my_champion_adress(&corewar);
  my_vm(&corewar);
  my_free();
  return (0);
}
