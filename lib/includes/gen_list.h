/*
** gen_list.h for Corewar in /home/paccar_c/rendu/corewar/lib/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:05:53 2015 Paccard Christopher
** Last update Sun Apr 12 15:52:26 2015 Paccard Christopher
*/

#ifndef GEN_LIST_H_
# define GEN_LIST_H_

typedef	struct s_list	t_list;

struct		s_list
{
  int		num_value_a;
  int		num_value_b;
  int		num_value_c;
  char		*str_value;
  t_list	*next;
  t_list	*prev;
};

t_list	*new_list(t_list *old, int numa, int numb, char *str);
t_list	*add_list_start(t_list *s, void *data);
void	free_list(t_list *s);
int	list_finder(t_list *s, char *label);

#endif /* !GEN_LIST_H_ */
