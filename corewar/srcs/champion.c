/*
** champion.c for corewar in /home/paccar_c/rendu/CPE_2014_corewar/corewar/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 09:37:03 2015 Paccard Christopher
** Last update Sun Apr 12 23:18:26 2015 Matthieu SISCA
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "champion.h"
#include "string_compare.h"
#include "nbr.h"
#include "my_fprintf.h"
#include "my_malloc.h"
#include "gen_list.h"

/*
** brief: parse the file to get the instructions of champions and informations
** @champion: our structure for each champion
** @file: name of the file given by the user
** return: {0 if succeed} {1 if not a corewar executable or problem with file}
*/
static unsigned int	my_champion_file(t_champion *champion, const char *file)
{
  int			fd;
  char			integer[4];

  if ((fd = open(file, O_RDONLY)) == -1)
    return (my_fprintf(2, "Can't open \"%s\".\n", file));
  if (read(fd, integer, 4) < 4)
    return (my_fprintf(2, "Not enough character for magic in \"%s\".\n", file));
  if (SWAP_ENDIAN(*((int*)integer)) != COREWAR_EXEC_MAGIC)
    return (my_fprintf(2, "Magic number is wrong in \"%s\".\n", file));
  if (read(fd, champion->name, PROG_NAME_LENGTH) < PROG_NAME_LENGTH)
    return (my_fprintf(2, "Not enough characters for name in \"%s\".\n", file));
  champion->name[PROG_NAME_LENGTH] = '\0';
  lseek(fd, 4, SEEK_CUR);
  if (read(fd, integer, 4) < 4)
    return (my_fprintf(2, "Not enough characters for size in \"%s\".\n", file));
  champion->size = SWAP_ENDIAN(*((int*)integer));
  if (read(fd, champion->comment, COMMENT_LENGTH) < COMMENT_LENGTH)
    return (my_fprintf(2, "Not enough characters for comm in \"%s\".\n", file));
  champion->comment[COMMENT_LENGTH] = '\0';
  lseek(fd, 4, SEEK_CUR);
  champion->code = my_malloc(champion->size * sizeof(champion->code));
  if (read(fd, champion->code, champion->size) < champion->size)
    return (my_fprintf(2, "Not enough characters for prog in \"%s\".\n", file));
  close(fd);
  return (0);
}

/*
** brief: parse the parameters given by the user for the champion
** @argc: number of arguments pass to the program
** @argv: each arguments pass to the program
** @i: our index of where we are in argv
** @champion: our structure for each champion
** return: {0 if succeed} {1 if number is not formated correctly}
*/
static int	my_champion_parameters(int argc, char **argv, int *i,
				       t_champion *champion)
{
  static int	number;

  if (*i < argc && !my_strcmp(argv[*i], "-n"))
    {
      if (*i + 1 >= argc || my_str_isnum(argv[*i + 1]) ||
	  (champion->number = my_getnbr(argv[*i + 1])) < 0)
	return (my_fprintf(2, "Champions must have a positive number.\n"));
      *i += 2;
    }
  else
    {
      champion->number = number;
      ++number;
    }
  if (*i < argc && !my_strcmp(argv[*i], "-a"))
    {
      if (*i + 1 >= argc || my_str_isnum(argv[*i + 1]) ||
	  (champion->address = my_getnbr(argv[*i + 1])) < 0)
	return (my_fprintf(2, "Champions must have a positive adress.\n"));
      *i += 2;
    }
  else
    champion->address = 0;
  return (0);
}

/*
** brief: fill the champion
** @argc: number of arguments pass to the program
** @argv: each arguments pass to the program
** @i: our index of where we are in argv
** @champion: our structure for each champion
** return: {0 if succeed} {1 if something went wrong}
*/
int	my_champion(int argc, char **argv, int *i, t_champion *champion)
{
  if (my_champion_parameters(argc, argv, i, champion))
    return (1);
  if (*i < argc)
    {
      if (my_champion_file(champion, argv[*i]))
	return (my_fprintf(2, "\"%s\" isn't a corewar executable\n", argv[*i]));
      champion->live = 0;
      champion->is_waiting = 0;
      ++*i;
    }
  else
    return (my_fprintf(2, "Parameters need a champion.\n"));
  return (0);
}
