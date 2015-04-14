/*
** string_copy.c for Corewar in /home/paccar_c/rendu/corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:35:15 2015 Paccard Christopher
** Last update Sun Mar 22 23:38:42 2015 Paccard Christopher
*/

#include <stdlib.h>
#include <string.h>
#include "my_malloc.h"

char		*my_strcpy(char *dest, const char *src)
{
  unsigned int	i;

  if (dest == NULL || src == NULL)
    return (NULL);
  i = 0;
  while (src[i] != '\0')
    {
      dest[i] = src[i];
      ++i;
    }
  dest[i] = '\0';
  return (dest);
}

char		*my_strncpy(char *dest, const char *src, const unsigned int n)
{
  unsigned int	i;

  if (dest == NULL || src == NULL)
    return (NULL);
  i = 0;
  while (src[i] != '\0' && i < n)
    {
      dest[i] = src[i];
      ++i;
    }
  dest[i] = '\0';
  return (dest);
}

char		*my_strcat(char *s1, const char *s2)
{
  char		*ret;
  unsigned int	i;
  unsigned int	j;

  i = 0;
  j = 0;
  if (!(ret = my_malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2)) + 1)))
    return (NULL);
  while (s1[i])
    {
      ret[j] = s1[i];
      ++j;
      ++i;
    }
  i = 0;
  while (s2[i])
    {
      ret[j] = s2[i];
      ++j;
      ++i;
    }
  ret[j] = '\0';
  return (ret);
}

char		*my_strncat(char *s1, const char *s2, const unsigned int nb)
{
  char		*ret;
  unsigned int	i;
  unsigned int	j;

  i = 0;
  j = 0;
  if (!(ret = my_malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2)) + 1)))
    return (NULL);
  while (s1[i])
    {
      ret[j] = s1[i];
      ++j;
      ++i;
    }
  i = 0;
  while (s2[i] && i != nb)
    {
      ret[j] = s2[i];
      ++j;
      ++i;
    }
  ret[j] = '\0';
  return (ret);
}
