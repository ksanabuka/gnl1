#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#include <stdlib.h>
#define BUFF_SIZE 50
#include "libft/libft.h"


  typedef  struct      s_mylist
{
    int             status;
    unsigned int    fd;
    char            *buffer;
    struct s_mylist   *next;
}                   t_fdlist;

int get_next_line(const int fd, char **line);

#endif 