/*
** check_param.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Sun Mar 22 23:43:58 2015 Paccard Christopher
** Last update Sun Apr 12 12:36:54 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "string.h"
#include "compile.h"
#include "my_fprintf.h"
#include "op.h"

/*
** Check if a single parameter (str) match type
** return -1 if it doesn't, else return 0
*/
int	my_check_param(args_type_t type, char *param)
{
  if (param == NULL)
    return (-1);
  if ((param[0] == DIRECT_CHAR) && ((type & T_DIR) != T_DIR))
    {
      my_fprintf(2, "%s param %s is direct", ERROR, param);
      return (-1);
    }
  else if ((param[0] == 'r') && ((type & T_REG) != T_REG))
    {
      my_fprintf(2, "%s param %s is registre", ERROR, param);
      return (-1);
    }
  else if (((param[0] != DIRECT_CHAR) && (param[0] != 'r'))
	   && ((type & T_IND) != T_IND))
    {
      my_fprintf(2, "%s param %s is indirect", ERROR, param);
      return (-1);
    }
  return (0);
}

/*
** Check if parameter in lexed_line match op
** return -1 if parameters doesn't match, else return 0
*/
int	my_check_params(int i, op_t *op, char **lexed_line)
{
  if (i - 1 > op->nbr_args)
    {
      my_fprintf(2, "%s too many params ", ERROR, i - 1, op->nbr_args);
      return (-1);
    }
  if (i - 1 < op->nbr_args)
    {
      my_fprintf(2, "%s not enough params ", ERROR, i - 1, op->nbr_args);
      return (-1);
    }
  if ((i - 1 >= 1 && my_check_param(op->type[0], lexed_line[1]) == -1)
      || (i - 1 >= 2 && my_check_param(op->type[1], lexed_line[2]) == -1)
      || (i - 1 >= 3 && my_check_param(op->type[2], lexed_line[3]) == -1))
    {
      my_fprintf(2, " : Invalid parameters ");
      return (-1);
    }
  return (0);
}

/*
** Check if str contain forbiden character
** return -1 if it does, else return 0
*/
int	check_if_valid_label(char *str)
{
  int	i;
  int	j;
  char	*valid_char;

  valid_char = LABEL_CHARS;
  i = 0;
  while (str[i])
    {
      j = 0;
      while (valid_char[j])
        {
          if (str[i] == valid_char[j] || str[i] == LABEL_CHAR)
            break;
          ++j;
        }
      if (!valid_char[j])
        {
          my_fprintf(2, "%s invalid char in label %s ", ERROR, str);
          return (-1);
        }
      ++i;
    }
  return (0);
}
