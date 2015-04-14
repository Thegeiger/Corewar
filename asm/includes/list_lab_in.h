/*
** list_lab_in.h for corwar in /home/rouss_p/rendu/CPE_2014_corewar/asm/includes
** 
** Made by pierre rousselle
** Login   <rouss_p@epitech.net>
** 
** Started on  Thu Mar 26 12:06:45 2015 pierre rousselle
** Last update Thu Apr  9 13:05:29 2015 pierre rousselle
*/

#ifndef	LIST_LAB_IN_H_
# define LIST_LAB_IN_H_

# include "gen_list.h"

typedef struct	s_latinfo
{
  int		nbrinstruction;
  t_list       	*label;
  t_list       	*label_call;
  t_list	*indirect_call;
}		t_lateinfo;

#endif /*!LIST_LAB_IN_H_*/
