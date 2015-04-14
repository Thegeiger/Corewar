/*
** label.c for corewar in /home/geiger_a/rendu/CPE_2014_corewar/asm
** 
** Made by anthony geiger
** Login   <geiger_a@epitech.net>
** 
** Started on  Thu Apr  9 14:52:24 2015 anthony geiger
** Last update Sun Apr 12 12:27:31 2015 Paccard Christopher
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "op.h"
#include "list_lab_in.h"
#include "get_argv.h"
#include "compile.h"
#include "string_copy.h"
#include "my_fprintf.h"
#include "write_argvs.h"
#include "string_compare.h"
#include "my_malloc.h"
#include "get_next_line.h"
#include "process.h"
#include "string.h"

/*
** write the size of the current program into the header
** return -1 in case of errror, else return 0
*/
int	header_size_prog(int fd_bin, int writed)
{
  int	fileoffset;

  fileoffset = writed;
  if (put_in_be((char *)(&fileoffset), sizeof(int)) == -1
      || lseek(fd_bin, 8 + PROG_NAME_LENGTH, SEEK_SET) == -1
      || write(fd_bin, (char *)(&fileoffset), sizeof(int)) == -1)
    {
      my_fprintf(2, "%s can't write progsize in header ", ERROR);
      return (-1);
    }
  return (0);
}

/*
** replace label reference by value stored in info
** return -1 in case of error, else return 0
*/
int		late_operation(int fd_bin, int writed, t_lateinfo *info)
{
  t_list	*tmp;
  int		dirval;

  if (header_size_prog(fd_bin, writed) == -1)
    return (-1);
  tmp = info->label_call;
  while (tmp != NULL)
    {
      if ((dirval = list_finder(info->label, tmp->str_value)) == -1)
        {
          my_fprintf(2, "%s unknown label ref ", ERROR, tmp->str_value);
          return (-1);
        }
      dirval -= tmp->num_value_c;
      if (put_in_be((char *)(&dirval), DIR_SIZE) == -1
	  || lseek(fd_bin, tmp->num_value_a + HEADER_SIZE + 8, SEEK_SET) == -1
          || write(fd_bin, (char *)(&dirval) + DIR_SIZE - tmp->num_value_b,
		   tmp->num_value_b) == -1)
        {
          my_fprintf(2, "%s while solving label ", ERROR);
          return (-1);
        }
      tmp = tmp->next;
    }
  return (0);
}

/*
** check if there is label definition in the current instruction
** if there is one, store it into info and delete it from the instruction
** return -1 in case of error, else return 0
*/
int	get_label_def(t_lateinfo *info, char **lexed_line, int fileoffset)
{
  char	*lab;
  int	i;

  if (lexed_line && lexed_line[0][0]
      && (lexed_line)[0][my_strlen((lexed_line)[0]) - 1] == LABEL_CHAR)
    {
      if (check_if_valid_label((lexed_line)[0]) == -1)
        return (-1);
      if ((lab = my_malloc(my_strlen((lexed_line)[0]) + 1)) == NULL
          || my_strcpy(lab, (lexed_line)[0]) == NULL)
        return (-1);
      if ((info->label = new_list(info->label, fileoffset, 0, lab)) == NULL)
	return (-1);
      i = 0;
      while (lexed_line[i])
        {
          lexed_line[i] = lexed_line[i + 1];
          ++i;
        }
    }
  return (0);
}

/*
** extension of get_lateparam
** return -1 in case of error, else return 0
*/
int		late_ext(t_lateinfo *info, char *word, int size, t_pos_info pos)
{
  char		*str;
  t_list	*tmp;

  if (word[1] == LABEL_CHAR)
    {
      if ((str = my_malloc(my_strlen(word) + 1)) == NULL
	  || my_strcpy(str, &(word[2])) == NULL)
	{
	  my_fprintf(2, "%s can't store label reference %s\n", ERROR, word);
	  return (-1);
	}
      if ((info->label_call = new_list(info->label_call, pos.whereiam,
				       size, str)) == NULL)
	return (-1);
      tmp = info->label_call;
      while (tmp != NULL && tmp->next != NULL)
	tmp = tmp->next;
      tmp->num_value_c = pos.to_cur_in;
      word[1] = '\0';
    }
  return (0);
}

/*
** check for label reference into the current instruction
** if there is at least one, store them into info
** return -1 in case of error, else return 0
*/
int	get_lateparam(t_lateinfo *info, char **lines, int offset, op_t *op)
{
  int	i;
  int	tmpoff;

  if (lines[0] == NULL)
    return (0);
  i = 1;
  tmpoff = 1 + (op->code == 1 || op->code == 9 || op->code == 12
		|| op->code == 15 ? 0 : 1);
  while (lines[i] != NULL)
    {
      if (lines[i][0] == DIRECT_CHAR)
        {
	  if (late_ext(info, lines[i], dirsize(op, i),
		       my_fuse(offset + tmpoff, offset)) == -1)
	    return (-1);
          tmpoff += dirsize(op, i);
        }
      else if (lines[i][0] == 'r')
        tmpoff += TRUE_REG_SIZE;
      else
        tmpoff += IND_SIZE;
      ++i;
    }
  ++(info->nbrinstruction);
  return (0);
}
