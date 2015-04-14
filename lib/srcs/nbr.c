/*
** nbr.c for nbr in /home/paccar_c/rendu/CPE_2014_corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Thu Apr  9 10:10:57 2015 Paccard Christopher
** Last update Sun Apr 12 16:02:51 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "string.h"

int		my_getnbr(const char *str)
{
  unsigned int	i;
  unsigned int	integer;
  char		sign;

  i = 0;
  integer = 0;
  sign = 1;
  while (str && ('0' > str[i] || str[i] > '9') && str[i] != '-')
    ++i;
  while (str && (str[i] == '-' || str[i] == '+') && str[i] != '\0')
    {
      sign = (str[i] == '-' ? -sign : sign);
      ++i;
    }
  if (str && ('0' > str[i] || str[i] > '9' || str[i] == '\0'))
    my_putstr_error("\33[33;1mWarning : \33[0mNo number, value will be 0.\n");
  while (str && ('0' <= str[i] && str[i] <= '9') && str[i] != '\0')
    {
      integer = (integer * 10) + (str[i] - '0');
      ++i;
    }
  if (integer > 2147483648 || (integer == 2147483648 && sign == 1))
    my_putstr_error("\33[33;1mWarning : \33[0mOverflow/Underflow detected.\n");
  return (integer * sign);
}

char	my_putnbr(int nbr)
{
  if (nbr < 0)
    {
      my_putchar('-');
      nbr = nbr * -1;
      my_putnbr(nbr);
    }
  else
    {
      if (nbr > 9)
        my_putnbr(nbr / 10);
      my_putchar(nbr % 10 + '0');
    }
  return (0);
}

unsigned int	my_str_isnum(const char *str)
{
  unsigned int	i;

  if (str == NULL)
    return (my_putstr_error("At my_str_isnum : string is NULL.\n"));
  i = 0;
  while (str[i] != '\0')
    {
      if ('0' > str[i] || str[i] > '9')
        return (1);
      ++i;
    }
  return (0);
}
