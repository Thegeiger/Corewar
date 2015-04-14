/*
** process.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Mon Mar 23 00:02:54 2015 Paccard Christopher
** Last update Sun Apr 12 18:53:38 2015 pierre rousselle
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "op.h"
#include "list_lab_in.h"
#include "get_argv.h"
#include "compile.h"
#include "my_fprintf.h"
#include "string_compare.h"
#include "my_malloc.h"

/*
** lauche the storage of label definition and reference
** get the member of op_tab (global from op.c) matching
** the instruction from lexed_line
** if there is a matching op_tab menmber, launch my_compil
** if any error is encountered or if the instruction doesn't
** exist in optab, return -1, else return 0
*/
int	process_line(char **lexed_line, int fd_binary,
		     int *fileoffset, t_lateinfo *info)
{
  int	i;
  int	ret;

  i = 0;
  if (get_label_def(info, lexed_line, *fileoffset) == -1)
    return (-1);
  while (op_tab[i].mnemonique != NULL && lexed_line[0] != NULL && **lexed_line)
    {
      if (my_strcmp(lexed_line[0], op_tab[i].mnemonique) == 0)
        {
	  if (get_lateparam(info, lexed_line, *fileoffset, &(op_tab[i])) == -1)
	    return (-1);
	  if ((ret = my_compil(lexed_line, &(op_tab[i]), fd_binary)) == -1)
	    return (-1);
	  *fileoffset += ret;
	  break;
        }
      ++i;
    }
  if (op_tab[i].mnemonique == NULL)
    {
      my_fprintf(2, "%s unknown opcode: %s ", ERROR, lexed_line[0]);
      return (-1);
    }
  return (0);
}

/*
** open the file str, and the file returned by get_fname
** if open doesn't fail, launch my_parsefile with fd of
** these two files.
** if open or my_parsefile return -1, return -1
** else return 0
*/
int	proces_file(char *str)
{
  char	*fname;
  int	fd_champ;
  int	fd_binary;
  char	fchar;

  fchar = 0;
  fname = &fchar;
  if ((fname = get_fname(fname, str)) == NULL)
    return (-1);
  if (((fd_champ = open(str, O_RDONLY)) == -1)
      || ((fd_binary = open(fname, (O_RDWR | O_CREAT | O_TRUNC),
			    (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))) == -1))
    {
      my_fprintf(2, "%s can't perform open(%s).\n", ERROR, str);
      return (-1);
    }
  if (my_parsefile(fd_champ, fd_binary) == -1)
    {
      my_fprintf(2, "at file %s.\n", str);
      return (-1);
    }
  close(fd_binary);
  close(fd_champ);
  return (0);
}

/*
** Return IND_SIZE or DIR_SIZE
** (check if operation and offset i mean that
** a direct arg will be writed as an index)
*/
int	dirsize(op_t *op, int i)
{
  return (((op->code == 10 || op->code == 14)
	   && (i == 1 || i == 2))
	  || op->code == 9
	  || (op->code == 11 && (i == 2 || i == 3))
	  || (op->code == 12)
	  || (op->code == 15)
	  ? IND_SIZE : DIR_SIZE);
}

/*
** put pos and instruc into a info
** return info
*/
t_pos_info	my_fuse(int pos, int instruc)
{
  t_pos_info	info;

  info.whereiam = pos;
  info.to_cur_in = instruc;
  return (info);
}
