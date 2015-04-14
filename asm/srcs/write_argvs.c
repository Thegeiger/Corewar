/*
** write_argvs.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Mon Mar 23 00:09:34 2015 Paccard Christopher
** Last update Sun Apr 12 21:54:12 2015 pierre rousselle
*/

#include <stdlib.h>
#include <unistd.h>
#include "op.h"
#include "get_next_line.h"
#include "my_fprintf.h"
#include "my_malloc.h"
#include "string_copy.h"
#include "nbr.h"
#include "string_compare.h"
#include "get_argv.h"
#include "compile.h"
#include "write_argvs.h"

/*
** write a single direct or indirect arg
** return -1 in case of error, else return 0
*/
int	my_sub_write_arg(char *str, int *writed, int bin, int cast)
{
  int	ret;
  int	arg;

  arg = my_getnbr(str);
  if (str[0] == DIRECT_CHAR)
    {
      if (arg >= 65536)
        my_fprintf(2, "%s direct is too big : %i\n", WARNING, arg);
      put_in_be((char *)&arg, (cast ? IND_SIZE : DIR_SIZE));
      if ((ret = write(bin, (char *)&arg, (cast ? IND_SIZE : DIR_SIZE))) == -1)
	return (-1);
      *writed += ret;
      return (0);
    }
  else
    {
      if (arg > IDX_MOD)
	my_fprintf(2, "%s indirection to far (%i)\n", WARNING, arg);
      put_in_be((char *)&arg, (IND_SIZE));
      if ((ret = write(bin, (char *)&arg, IND_SIZE)) ==  -1)
	return (-1);
      *writed += ret;
      return (0);
    }
  return (-1);
}

/*
** write a single arg
** return -1 in case of error, else return 0
*/
int	my_write_arg(int *writed, int fd_binary, char *str, int cast)
{
  int	arg;
  int	ret;

  arg = my_getnbr(str);
  if (str[0] == 'r')
    {
      if (arg < 1 || arg > REG_NUMBER)
	my_fprintf(2, "%s no such register %i\n", WARNING, arg);
      if ((ret = write(fd_binary, (char *)(&arg), TRUE_REG_SIZE)) ==  -1)
	return (-1);
      *writed += ret;
      return (0);
    }
  if (my_sub_write_arg(str, writed, fd_binary, cast) == -1)
    return (-1);
  return (0);
}

/*
** write the coding byte of the current instruction
** return how many byte has been writed
*/
int	my_write_oct_code(char **lexed, op_t *op, int fd_binary, int writed)
{
  int	ret;
  char	oct_code;

  if (op->code != 1 && op->code != 12 && op->code != 15 && op->code != 9)
    {
      oct_code = 0;
      if (lexed[1])
        {
	  oct_code |= (lexed[1][0] == 'r' ? 0x40 :
		       (lexed[1][0] == DIRECT_CHAR ? 0x80 : 0xc0));
	  if (lexed[2])
	    {
	      oct_code |= (lexed[2][0] == 'r' ? 0x10 :
			   (lexed[2][0] == DIRECT_CHAR ? 0x20 : 0x30));
	      if (lexed[3])
		oct_code |= (lexed[3][0] == 'r' ? 0x4 :
			     (lexed[3][0] == DIRECT_CHAR ? 0x8 : 0xc));
	    }
        }
      if ((ret = write(fd_binary, &oct_code, 1)) == -1)
        return (-1);
      writed += ret;
    }
  return (writed);
}

/*
** lauche the writing operation of the coding byte for current instruction
** write every args of the current instruction
** if an error is encountered, return -1
** else return how many byte has been writed
*/
int	my_write_args(char **lexed_line, op_t *optodo, int fd_binary)
{
  int	writed;
  int	ret;
  int	i;

  writed = 0;
  if ((ret = my_write_oct_code(lexed_line, optodo, fd_binary, 0)) == -1)
    return (-1);
  writed += ret;
  i = 1;
  if (lexed_line[0])
    while (lexed_line[i])
      {
	if (my_write_arg(&writed, fd_binary, lexed_line[i],
			 ((((optodo->code == 10 || optodo->code == 14)
			    && (i == 1 || i == 2))
			   || optodo->code == 9
			   || optodo->code == 12
			   || optodo->code == 15
			   || (optodo->code == 11 && (i == 2 || i == 3)))
			  ? 1 : 0)) == -1)
	  return (-1);
	++i;
      }
  return (writed);
}
