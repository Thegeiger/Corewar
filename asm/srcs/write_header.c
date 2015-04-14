/*
** write_header.c for corewar in /home/rouss_p/rendu/CPE_2014_corewar/asm/srcs
** 
** Made by pierre rousselle
** Login   <rouss_p@epitech.net>
** 
** Started on  Wed Apr  1 09:09:43 2015 pierre rousselle
** Last update Sun Apr 12 12:12:56 2015 Paccard Christopher
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "op.h"
#include "list_lab_in.h"
#include "get_argv.h"
#include "compile.h"
#include "my_fprintf.h"
#include "string.h"
#include "string_copy.h"
#include "string_compare.h"
#include "my_malloc.h"
#include "get_next_line.h"
#include "string.h"

/*
** fill header struct with name and comment
** return -1 in case of error, else return 0
*/
int	get_name_comment(char *line, header_t *header,
			 char *isdonename, char *isdonecom)
{
  if (my_strncmp(line, NAME_CMD_STRING, my_strlen(NAME_CMD_STRING)) == 0)
    {
      if (*isdonename != 0)
        {
          my_fprintf(2, "%s too many names ", ERROR);
          return (-1);
        }
      ++(*isdonename);
      if (get_quotes_name(line, header->prog_name) == NULL)
        return (-1);
    }
  if (my_strncmp(line, COMMENT_CMD_STRING, my_strlen(COMMENT_CMD_STRING)) == 0)
    {
      if (*isdonecom != 0)
        {
          my_fprintf(2, "%s too many comment ", ERROR);
          return (-1);
        }
      ++(*isdonecom);
      if (get_quotes_comment(line, header->comment) == NULL)
        return (-1);
    }
  return (0);
}

/*
** switch arg endian
** return -1 in case of error, else return 0
*/
int	put_in_be(char *arg, int size)
{
  char	*buffer;
  int	i;
  int	j;

  if ((buffer = my_malloc(size + 1)) == NULL)
    return (-1);
  i = 0;
  while (i < size)
    buffer[i++] = '\0';
  if (size == 2 || size == 4)
    buffer[0] = arg[0];
  if (size == 2 || size == 4)
    buffer[1] = arg[1];
  if (size == 4)
    buffer[2] = arg[2];
  if (size == 4)
    buffer[3] = arg[3];
  i = size - 1;
  j = 0;
  while (i >= 0)
    arg[i--] = buffer[j++];
  return (0);
}

/*
** extension of write_header
** return -1 in case of error, else return 0
*/
int	write_header_ext(int fd_bin, int fd_champ, header_t *header)
{
  int	writed;

  header->magic = COREWAR_EXEC_MAGIC;
  if (put_in_be((char *)(&header->magic), sizeof(int)) == -1)
    return (-1);
  writed = 0;
  writed += write(fd_bin, (char *)(&header->magic), sizeof(int));
  writed += write(fd_bin, header->prog_name, PROG_NAME_LENGTH);
  writed += write(fd_bin, "\0\0\0\0\0\0\0\0", 8);
  writed += write(fd_bin, header->comment, COMMENT_LENGTH);
  writed += write(fd_bin, "\0\0\0\0", 4);
  writed += lseek(fd_champ, 0, SEEK_SET);
  if (writed != 8 + PROG_NAME_LENGTH + COMMENT_LENGTH + 4 + 4)
    {
      my_fprintf(2, "%s can't write header ", ERROR);
      return (-1);
    }
  return (0);
}

/*
** write header for current program
** return -1 in case of error, else return 0
*/
int		write_header(int fd_champ, int fd_bin)
{
  char		isdonename;
  char		isdonecom;
  header_t	header;
  char		*line;
  int		i;

  i = 0;
  while (i < PROG_NAME_LENGTH + 1)
    header.prog_name[i++] = '\0';
  i = 0;
  while (i < COMMENT_LENGTH + 1)
    header.comment[i++] = '\0';
  isdonecom = 0;
  isdonename = 0;
  while ((line = get_next_line(fd_champ)) && isdonename + isdonecom < 2)
    {
      if (get_name_comment(line, &header, &isdonename, &isdonecom) == -1)
        return (-1);
    }
  if (isdonename + isdonecom != 2)
    {
      my_fprintf(2, "%s name or comment needed ", ERROR);
      return (-1);
    }
  return (write_header_ext(fd_bin, fd_champ, &header));
}
