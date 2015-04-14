/*
** string_compare.c for Corewar in /home/paccar_c/rendu/corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:34:22 2015 Paccard Christopher
** Last update Wed Apr  1 10:52:01 2015 pierre rousselle
*/

#include <stdlib.h>
#include "string.h"

int		 my_strcmp(const char *s1, const char *s2)
{
  unsigned int	i;

  if (s1 == NULL || s2 == NULL)
    {
      my_putstr_error("One of the string is NULL in my_strcmp.\n");
      return (-1);
    }
  i = 0;
  while (s1[i] != '\0' && s2[i] != '\0')
    {
      if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
      ++i;
    }
  if ((s1[i] && !s2[i]) || (!s1[i] && s2[i]))
    return (-1);
  return (0);
}

int		my_strncmp(const char *s1, const char *s2, const unsigned int n)
{
  unsigned int	i;

  if (s1 == NULL || s2 == NULL)
    {
      my_putstr_error("One of the string is NULL in my_strncmp.\n");
      return (-1);
    }
  i = 0;
  while (s1[i] != '\0' && s2[i] != '\0' && i < n)
    {
      if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
      ++i;
    }
  return (0);
}
