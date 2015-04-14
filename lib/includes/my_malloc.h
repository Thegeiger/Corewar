/*
** my_malloc.h for Corewar in /home/paccar_c/rendu/corewar/lib/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:09:06 2015 Paccard Christopher
** Last update Sun Mar 22 23:20:53 2015 Paccard Christopher
*/

#ifndef MY_MALLOC_H_
# define MY_MALLOC_H_

typedef struct s_glist	t_glist;

struct		s_glist
{
  void		*data;
  t_glist	*next;
  t_glist	*prev;
};

t_glist	*new_glist(t_glist* old, void* data);
t_glist	*add_glist_start(t_glist *s, void *data);
void	free_glist(t_glist *s);
void	*my_malloc(const unsigned int size);
void	my_free();

#endif /* !MY_MALLOC_H_ */
