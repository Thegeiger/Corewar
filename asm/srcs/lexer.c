/*
** lexer.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Sun Mar 22 23:55:47 2015 Paccard Christopher
** Last update Sun Apr 12 12:35:44 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "string.h"
#include "op.h"
#include "my_malloc.h"
#include "lexer.h"

int	my_add_all(int *i, char *str, int *j, char **tabl)
{
  int	x;
  int	len;

  len = my_strlen(str);
  x = 0;
  if (str[*j] != '\0')
    {
      (*i)++;
      x = 0;
      if ((tabl[*i] = my_malloc(sizeof(char *) * len + 1)) == NULL)
	return (1);
      while (str[*j] == SEPARATOR_CHAR || str[*j] == SEPARATOR_CHAR2
	     || str[*j] == '\t')
	{
	  tabl[*i][x] = str[*j];
	  (*j)++;
	  ++x;
	}
      tabl[*i][x] = '\0';
    }
  (*i)++;
  return (0);
}

void	my_init_nx(int *n, int *x)
{
  *x = 0;
  *n = 0;
}

void	my_add_param(char *str, int *j, char **tabl, int i)
{
  int	n;
  int	x;

  my_init_nx(&n, &x);
  while (str[*j] == SEPARATOR_CHAR || str[*j] == SEPARATOR_CHAR2
	 || str[*j] == '\t')
    (*j)++;
  while (str[*j] != SEPARATOR_CHAR && str[*j] != '\t'
	 && str[*j] != SEPARATOR_CHAR2 && str[*j] != '\0')
    {
      if (str[*j] == ' ')
      	{
      	  n = 1;
      	  (*j)++;
      	  continue;
      	}
      if (n == 1)
      	{
      	  tabl[i][x] = ' ';
      	  x++;
      	}
      tabl[i][x++] = str[(*j)++];
      n = 0;
    }
  tabl[i][x] = '\0';
}

char	**all_in_tab_base(char *str, int word)
{
  char	**tabl;
  int	i;
  int	len;
  int	j;

  i = 0;
  j = 0;
  len = my_strlen(str);
  if ((tabl = my_malloc(sizeof(char *) * (word + 2))) == NULL)
    return (NULL);
  while (i < word)
    {
      if ((tabl[i] = my_malloc(sizeof(char *) * (len + 1))) == NULL)
	return (NULL);
      if (str[j] == ' ')
	j++;
      my_add_param(str, &j, tabl, i);
      i++;
    }
  if (tabl[i - 1][0] == '\0')
    tabl[i - 1] = NULL;
  tabl[i] = NULL;
  return (tabl);
}

char	**all_in_tab(char *str)
{
  int	i;
  int	word;

  i = 0;
  word = 1;
  while (str[i])
    {
      if (str[i] == SEPARATOR_CHAR
	  || str[i] == SEPARATOR_CHAR2 || str[i] == '\t')
	{
	  i++;
	  ++word;
	  while ((str[i] == SEPARATOR_CHAR
		  || str[i] == SEPARATOR_CHAR2 || str[i] == '\t')
		 && str[i] != '\0')
	    i++;
	}
      else
	i++;
    }
  return (all_in_tab_base(str, word));
}
