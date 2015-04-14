/*
** compile.h for Corewar in /home/paccar_c/rendu/corewar/asm/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:40:11 2015 Paccard Christopher
** Last update Sun Apr 12 11:55:13 2015 Paccard Christopher
*/

#ifndef _COMPILE_H_
# define _COMPILE_H_

# include "list_lab_in.h"
# include "op.h"
# define HEADER_SIZE (8 + PROG_NAME_LENGTH + COMMENT_LENGTH)
# define WARNING "\33[33;1mWarning :\33[0m"
# define ERROR "\33[31;1mError :\33[0m"
# define NOTE "\33[32;1mNote :\33[0m"

typedef struct	s_pos_info
{
  int		whereiam;
  int		to_cur_in;
}		t_pos_info;

t_pos_info	my_fuse(int pos, int instruc);
int		my_compil(char **lexed_line, op_t *optodo, int fd_binary);
int		my_parsefile(int fd_champ, int fd_binary);
char		*get_quotes(const char *str);
int		header_size_prog(int fd_bin, int writed);
int		late_operation(int fd_bin, int writed, t_lateinfo *info);
int		check_if_valid_label(char *str);
int		get_label_def(t_lateinfo *info, char **lexed_line,
			      int fileoffset);
int		get_lateparam(t_lateinfo *info, char **lexed_line,
			      int fileoffset, op_t *optodo);
char		*put_in_char(int nbr, int size);

#endif /* !_COMPILE_H_ */
