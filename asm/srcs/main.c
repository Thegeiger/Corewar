/*
** main.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Mon Mar 23 00:02:18 2015 Paccard Christopher
** Last update Sun Apr 12 12:25:35 2015 Paccard Christopher
*/

#include "op.h"
#include "string.h"
#include "process.h"
#include "compile.h"
#include "my_malloc.h"
#include "my_fprintf.h"

/*
** for every argument of the program,
** launch process_file.
*/
int	main(int argc, char **argv)
{
  int	i;

  i = 1;
  if (argc == 1)
    {
      my_fprintf(2, "Usage : ./asm [file to compil]\n");
      return (-1);
    }
  while (i != argc)
    {
      if (proces_file(argv[i]) == -1)
	my_fprintf(2, "%s \"%s\" assembly failed.\n", ERROR, argv[i]);
      else
	my_fprintf(1, "%s \"%s\" assembled.\n", NOTE, argv[i]);
      ++i;
    }
  my_free();
  return (42);
}
