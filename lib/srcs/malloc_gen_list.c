/*
** malloc_gen_list.c for Corewar in /home/paccar_c/rendu/corewar/lib/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:23:46 2015 Paccard Christopher
** Last update Sun Apr 12 16:04:25 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "my_malloc.h"

t_glist		*new_glist(t_glist* old, void* data)
{
  t_glist	*new;
  t_glist	*tmp;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = NULL;
  new->prev = NULL;
  new->data = data;
  if (old == NULL)
    return (new);
  tmp = old;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  new->prev = tmp;
  return (old);
}

void		free_glist(t_glist *s)
{
  t_glist	*tmp;

  tmp = s;
  while (tmp->next != NULL)
    tmp = tmp->next;
  while (tmp->prev != NULL)
    {
      tmp = tmp->prev;
      free(tmp->next);
    }
  free(tmp);
}
