/*
** ldi.h for Corewar in /home/sisca_m/rendu/CPE_2014_corewar/corewar/includes
**
** Made by Matthieu SISCA
** Login   <sisca_m@epitech.net>
**
** Started on  Fri Apr 10 01:44:38 2015 Matthieu SISCA
** Last update Sun Apr 12 21:00:21 2015 Paccard Christopher
*/

#ifndef LDI_H_
# define LDI_H_

int	my_sec_arg(t_champion *champion, unsigned char **arena,
		   char codage, int i);
int	ldi_reg(t_champion *champion, unsigned char **arena, char codage);
int	ldi(t_champion *champion, unsigned char **arena);

#endif /* !LDI_H_ */
