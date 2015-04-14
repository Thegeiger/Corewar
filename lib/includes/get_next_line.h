/*
** get_next_line.h for Corewar in /home/paccar_c/rendu/corewar/lib/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:07:48 2015 Paccard Christopher
** Last update Tue Mar 24 10:07:39 2015 pierre rousselle
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUF_SIZE (1)

typedef struct	s_char
{
  char		character;
  struct s_char	*next;
}		t_char;

char	*get_next_line(const int fd);

#endif /* !GET_NEXT_LINE_H_ */
