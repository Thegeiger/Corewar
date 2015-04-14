/*
** my_malloc.c for Corewar in /home/paccar_c/rendu/corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:26:14 2015 Paccard Christopher
** Last update Sun Apr 12 16:04:04 2015 Paccard Christopher
*/

#include <unistd.h>
#include <stdlib.h>
#include "my_malloc.h"

static t_glist	*g_save = NULL;

static int	save_malloced(void *data)
{
  if ((g_save = new_glist(g_save, data)) == NULL)
    return (-1);
  return (0);
}

void	*my_malloc(const unsigned int size)
{
  void	*malloced;

  if ((malloced = malloc(size)) == NULL)
    {
      write(2, "malloc of size failed\n", 22);
      return (NULL);
    }
  if (save_malloced(malloced) == -1)
    return (NULL);
  return (malloced);
}

void		my_free()
{
  t_glist	*tmp;

  tmp = g_save;
  if (tmp == NULL)
    return ;
  while (tmp->next != NULL)
    tmp = tmp->next;
  while (tmp != NULL)
    {
      free(tmp->data);
      tmp = tmp->prev;
    }
  free_glist(g_save);
}
