/*
** process.h for Corewar in /home/paccar_c/rendu/corewar/asm/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:42:15 2015 Paccard Christopher
** Last update Thu Apr  9 11:12:59 2015 pierre rousselle
*/

#ifndef _PROCESS_H_
# define _PROCESS_H_

# include "list_lab_in.h"
# include "op.h"

int	process_line(char **lexed_line, int fd_binary,
		     int *fileoffset, t_lateinfo *info);
int	proces_file(char *str);
void    dir_to_ind(char **lines, op_t *op);
int	dirsize(op_t *op, int i);

#endif /* !_PROCESS_H_ */
