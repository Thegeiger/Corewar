/*
** write_argvs.h for Corewar in /home/paccar_c/rendu/corewar/asm/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:42:40 2015 Paccard Christopher
** Last update Wed Apr  8 17:17:08 2015 pierre rousselle
*/

#ifndef _WRITE_ARGVS_H_
# define _WRITE_ARGVS_H_

# define TRUE_REG_SIZE 1
# define TRUE_DIR_SIZE 2

int	my_write_arg(int *writed, int fd_binary, char *str, int cast);
int	my_write_args(char **lexed_line, op_t *optodo, int fd_binary);
int	write_header(int fd_champ, int fd_bin);
int     get_name_comment(char *line, header_t *header,
			 char *isdonename, char *isdonecom);
int     put_in_be(char *arg, int size);
int     write_header_ext(int fd_bin, int fd_champ, header_t *header);
int     write_header(int fd_champ, int fd_bin);

#endif /* !_WRITE_ARGVS_H_ */
