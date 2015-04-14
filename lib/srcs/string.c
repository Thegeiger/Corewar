/*
** string.c for Corewar in /home/paccar_c/rendu/corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:29:14 2015 Paccard Christopher
** Last update Sun Mar 22 23:34:10 2015 Paccard Christopher
*/

#include <stdlib.h>
#include <unistd.h>

char	my_putchar(const char c)
{
  return (write(1, &c, 1));
}

int		my_strlen(const char *str)
{
  unsigned int	i;

  if (str == NULL)
    return (-1);
  i = 0;
  while (str[i] != '\0')
    ++i;
  return (i);
}

int	my_putstr_error(const char *str)
{
  if (str == NULL)
    return (-1);
  if (write(2, str, my_strlen(str)) == -1)
    {
      if ((write(1, "Can't write on fd: 2\n", 24)) == -1)
	exit(1);
    }
  return (1);
}

int	my_tablen(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    ++i;
  return (i);
}

int		my_putstr(const char *str)
{
  unsigned int	length;

  if (str == NULL)
    return (-1);
  length = my_strlen(str);
  if (write(1, str, length) == -1)
    {
      if ((write(2, "Can't write on fd: 1\n", 24)) == -1)
	exit(1);
    }
  return (length);
}
