/*
** my_fprintf.c for my_fprintf in /home/paccar_c/rendu/CPE_2014_corewar/lib/srcs
**
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
**
** Started on  Thu Apr  9 10:15:07 2015 Paccard Christopher
** Last update Sun Apr 12 17:58:57 2015 Matthieu SISCA
*/

#include <unistd.h>
#include <stdarg.h>
#include "string.h"

static void	my_fputnbr(const int fd, int nbr)
{
  char		c;

  if (nbr < 0)
    {
      write(fd, "-", 1);
      nbr = nbr * -1;
      my_fputnbr(fd, nbr);
    }
  else
    {
      if (nbr > 9)
        my_fputnbr(fd, nbr / 10);
      c = nbr % 10 + '0';
      write(fd, &c, 1);
    }
}

static void	my_fputhex(const int fd, unsigned int nbr)
{
  char	hex[2];
  char	*base;

  base = "0123456789ABCDEF";
  hex[1] = base[nbr % 16];
  nbr /= 16;
  hex[0] = base[nbr % 16];
  write(fd, hex, 2);
}

static void	my_flag(const int fd, const char flag, va_list *args)
{
  char		*str;

  if (flag == 's')
    {
      str = va_arg(*args, char*);
      if (fd == 1)
	my_putstr(str);
      else
	my_putstr_error(str);
    }
  else if (flag == 'i')
    my_fputnbr(fd, va_arg(*args, int));
  else if (flag == 'x')
    my_fputhex(fd, va_arg(*args, int));
  else
    write(fd, &flag, 1);
}

int		my_fprintf(const int fd, const char *format, ...)
{
  va_list	args;
  int		i;

  i = 0;
  va_start(args, format);
  while (format && format[i] != '\0')
    {
    while (format[i] != '\0' && format[i] != '%')
      {
	write(fd, &format[i], 1);
	++i;
      }
    if (format[i] == '%')
      {
        ++i;
        my_flag(fd, format[i], &args);
        if (format[i] != '\0')
          ++i;
      }
    }
  va_end(args);
  return ((fd == 1 ? 0 : 1));
}
