/*
** get_next_line.c for COrewar in /home/paccar_c/rendu/corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:21:18 2015 Paccard Christopher
** Last update Sun Apr 12 16:04:45 2015 Paccard Christopher
*/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

static int	my_put_in_list(t_char **list, const char character)
{
  t_char	*elem;

  elem = malloc(sizeof(*elem));
  if (elem == NULL)
    return (1);
  elem->character = character;
  elem->next = *list;
  *list = elem;
  return (0);
}

static int	my_list_size(t_char *list)
{
  t_char	*tmp;
  int		counter;

  tmp = list;
  counter = 0;
  while (tmp != NULL)
    {
      tmp = tmp->next;
      counter = counter + 1;
    }
  return (counter);
}

static char	*my_convlist(t_char *list)
{
  int		counter;
  char		*str;
  t_char	*tmp;

  counter = my_list_size(list);
  if (counter >= 0)
    {
      str = malloc(my_list_size(list) * sizeof(*str) + 1);
      if (str == NULL)
	return (NULL);
      str[counter--] = '\0';
      while (list != NULL)
      	{
	  tmp = list;
      	  str[counter--] = list->character;
	  list = list->next;
      	  free(tmp);
      	}
      return (str);
    }
  return (NULL);
}

char			*get_next_line(const int fd)
{
  static char		buf[BUF_SIZE];
  static int		r;
  static int		i;
  static t_char		*tmp_buf;
  char			*str;

  i = ((i >= BUF_SIZE || i == r) ? (0) : (i));
  if (i >= BUF_SIZE || i == 0)
    r = read(fd, buf, BUF_SIZE);
  str = ((r == 0 && tmp_buf != NULL) ? (my_convlist(tmp_buf)) : (NULL));
  while (r > 0 && i != r)
    {
      while (i != r && buf[i] != '\n')
	my_put_in_list(&tmp_buf, buf[i++]);
      if (buf[i] == '\n')
	{
	  i = i + 1;
	  str = my_convlist(tmp_buf);
	  tmp_buf = NULL;
	  break;
	}
      return (get_next_line(fd));
    }
  tmp_buf = NULL;
  return (str);
}
