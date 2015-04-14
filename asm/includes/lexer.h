/*
** lexer.h for Corewar in /home/paccar_c/rendu/corewar/asm/includes
** 
** Made by Paccard Christopher
** Login   <paccar_c@epitech.net>
** 
** Started on  Sun Mar 22 23:41:33 2015 Paccard Christopher
** Last update Thu Apr  9 14:38:08 2015 pierre rousselle
*/

#ifndef _LEXER_H_
# define _LEXER_H_

# define SEPARATOR_CHAR2 ' '

int	my_add_all(int *i, char *str, int *j, char **tabl);
void	my_add_param(char *str, int *j, char **tabl, int i);
char	**all_in_tab_base(char *str, int word);
char	**all_in_tab(char *str);
void	remove_str_in_tab(char **tab, int x);

#endif /* !_LEXER_H_ */
