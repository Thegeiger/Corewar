/*
** gen_list.c for Corewar in /home/paccar_c/rendu/corewar/asm/srcs
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:47:19 2015 Paccard Christopher
** Last update Sun Apr 12 12:28:45 2015 Paccard Christopher
*/

#include <stdlib.h>
#include "gen_list.h"
#include "string.h"
#include "string_compare.h"
#include "op.h"

/*
** Add an element at the end of old
** Return the first link of old, or NULL if it can't allocat memory
** for the new link
*/
t_list		*new_list(t_list *old, int num_a, int num_b, char *str)
{
  t_list	*new;
  t_list	*tmp;

  if ((new = malloc(sizeof(*new))) == NULL)
    return (NULL);
  new->next = NULL;
  new->prev = NULL;
  new->num_value_a = num_a;
  new->num_value_b = num_b;
  new->str_value = str;
  if (old == NULL)
    return (new);
  tmp = old;
  while (tmp->next != NULL)
    tmp = tmp->next;
  tmp->next = new;
  new->prev = tmp;
  return (old);
}

/*
** free every link of the list s
*/
void		free_list(t_list *s)
{
  t_list	*tmp;

  if (s == NULL)
    return ;
  tmp = s;
  while (tmp->next != NULL)
    tmp = tmp->next;
  while (tmp->prev != NULL)
    {
      tmp = tmp->prev;
      free(tmp);
    }
}

/*
** return -1 if label and src differ, else return 0
** if the last character of str is LABEL_CHAR, it is
** overwritted with a '\0'
*/
int	my_strcmp_lab(char *label, char *str)
{
  int	i;

  if (str[my_strlen(str) - 1] == LABEL_CHAR)
    str[my_strlen(str) - 1] = '\0';
  i = 0;
  while (label[i] && str[i])
    {
      if (str[i] != label[i])
	return (-1);
      ++i;
    }
  if ((!str[i] && label[i]) || (str[i] && !label[i]))
    return (-1);
  return (0);
}

/*
** return the member num_value_a of the oldest link of s
** where str_value match label
** if no link match, return -1
*/
int		list_finder(t_list *s, char *label)
{
  t_list	*tmp;

  tmp = s;
  while (tmp != NULL && my_strcmp_lab(label, (char*)tmp->str_value) != 0)
    tmp = tmp->next;
  if (tmp == NULL)
    return (-1);
  return (tmp->num_value_a);
}
