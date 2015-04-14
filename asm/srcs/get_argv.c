/*
** get_argv.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Mon Mar 23 00:13:21 2015 Paccard Christopher
** Last update Sun Apr 12 12:32:15 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "string_compare.h"
#include "my_fprintf.h"
#include "string_copy.h"
#include "string.h"
#include "op.h"
#include "compile.h"

/*
** Return and store into fname str with a ".cor" at the end
** if str is terminated by a ".s", it is replaced with a ".cor"
** Return NULL in case of error
*/
char	*get_fname(char *fname, char *str)
{
  if (my_strcmp(str + (my_strlen(str) >= 2 ?
		       my_strlen(str) - 2 : 0), ".s") == 0)
    {
      if ((fname = my_strncat(fname, str, (my_strlen(str) - 2))) == NULL)
	return (NULL);
    }
  else
    if ((fname = my_strcat(fname, str)) == NULL)
      return (NULL);
  if ((fname = my_strcat(fname, ".cor")) == NULL)
    return (NULL);
  return (fname);
}

/*
** fill and return ret with content of the substring of str
** between two \"
** in ase of error, return NULL
*/
char		*get_quotes_comment(const char *str, char ret[])
{
  unsigned int	i;
  unsigned int	j;
  unsigned int	k;

  i = 0;
  j = 0;
  while (str[i] && str[i] != '\"')
    ++i;
  if (!str[i])
    {
      my_fprintf(2, "%s wrong comment ", ERROR);
      return (NULL);
    }
  ++i;
  k = i;
  while (str[k] && str[k] != '\"' && k <= COMMENT_LENGTH)
    ret[j++] = str[k++];
  if (str[k] != '\"')
    {
      my_fprintf(2, "%s wrong comment ", ERROR);
      return (NULL);
    }
  while (k <= COMMENT_LENGTH + 1)
    ret[k++] = '\0';
  return (ret);
}

/*
** fill and return ret with content of the substring of str
** between two \"
** in ase of error, return NULL
*/
char		*get_quotes_name(const char *str, char ret[])
{
  unsigned int	i;
  unsigned int	j;
  unsigned int	k;

  i = 0;
  j = 0;
  while (str[i] && str[i] != '\"')
    ++i;
  if (!str[i])
    {
      my_fprintf(2, "%s wrong name ", ERROR);
      return (NULL);
    }
  ++i;
  k = i;
  while (str[k] && str[k] != '\"' && k <= PROG_NAME_LENGTH)
    ret[j++] = str[k++];
  if (str[k] != '\"')
    {
      my_fprintf(2, "%s wrong name ", ERROR);
      return (NULL);
    }
  while (k <= PROG_NAME_LENGTH + 1)
    ret[k++] = '\0';
  return (ret);
}
