/*
** compil.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:45:22 2015 Paccard Christopher
** Last update Sun Apr 12 12:31:29 2015 Paccard Christopher
*/

#include <unistd.h>
#include "stdlib.h"
#include "list_lab_in.h"
#include "process.h"
#include "get_next_line.h"
#include "my_fprintf.h"
#include "op.h"
#include "string.h"
#include "list_lab_in.h"
#include "my_malloc.h"
#include "check.h"
#include "write_argvs.h"
#include "get_next_line.h"
#include "lexer.h"
#include "compile.h"

/*
** compil a single instruction (lexed_line):
** check the params and write the einstruction
** if an error is encountered, return -1
** else return how many byte has been writed
*/
int	my_compil(char **lexed_line, op_t *optodo, int fd_binary)
{
  int	i;
  int	ret;
  int	writed;

  writed = 0;
  i = my_tablen(lexed_line);
  if (my_check_params(i, optodo, lexed_line) == -1)
    return (-1);
  if ((ret = write(fd_binary, &(optodo->code), 1)) == -1)
    {
      my_fprintf(2, "write() error. (opcode)\n");
      return (-1);
    }
  writed += ret;
  if ((ret = my_write_args(lexed_line, optodo, fd_binary)) == -1)
    {
      my_fprintf(2, "write() error. (arg)\n");
      return (-1);
    }
  writed += ret;
  return (writed);
}

/*
** Init member of info at (void *)0
*/
void	my_init_info(t_lateinfo *info)
{
  info->nbrinstruction = 0;
  info->label = NULL;
  info->label_call = NULL;
  info->indirect_call = NULL;
}

/*
** Delete comment from tab
** (end the tab when a comment is encountered)
** return the epurated tab (if tab is NULL, return NULL)
*/
char	**my_epur(char **tab)
{
  int	i;
  int	j;

  i = 0;
  if (tab != NULL)
    while (tab[i])
      {
	j = 0;
	while (tab[i][j])
	  {
	    if (tab[i][j] == COMMENT_CHAR)
	      {
		tab[i][j] = '\0';
		tab[i + 1] = NULL;
		if (j == 0 && i != 0)
		  {
		    tab[i] = NULL;
		    break ;
		  }
	      }
	    ++j;
	  }
	++i;
      }
  return (tab);
}

/*
** Write the header of the file (minus the prog size)
** init the linked lists storing label definition and reference
** Read every line of the file fd_champ,
** split them into a word tab and send them
** to process_line
** Then launch late_operation
** if any error is encountered during these operations,
** return -1, else return 0
*/
int		my_parsefile(int fd_champ, int fd_binary)
{
  char		*line;
  char		**lexed_line;
  int		j;
  int		fileoffset;
  t_lateinfo	info;

  my_init_info(&info);
  if ((fileoffset = write_header(fd_champ, fd_binary)) == -1)
    return (-1);
  j = 1;
  while ((line = get_next_line(fd_champ)) != NULL)
    {
      if (line[0] != COMMENT_CHAR && line[0] != '.' && line[0] && line[0])
	{
	  if ((lexed_line = my_epur(all_in_tab(line))) == NULL
	      || process_line(lexed_line, fd_binary, &fileoffset, &info) == -1)
	    {
	      my_fprintf(2, "at line %i : \"%s\" ", j, line);
	      return (-1);
	    }
	}
      free(line);
      ++j;
    }
  return (late_operation(fd_binary, fileoffset, &info));
}
