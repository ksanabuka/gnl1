
#include "gnl.h"

int check_update_mem_capacity(char **line, t_size csize, t_size capacity)
{
    char * new;

    if (capacity - 1 == csize || (capacity < csize))
    {
        capacity += BUFF_SIZE;
        new =  (char *)ft_memalloc(capacity);
        if (!new)
            return 0;
        new = ft_memmove(new, *line, ft_strlen(*p_buf));
        ft_memdel((void**)line);
        *line = new;
    }
    
    return capacity;
}

int get_next_line(const int fd, char **line)
{

    int bytesread; 
    char *buf;
    char ** p_buf;
    t_size i = 0;
    char c;
    line = &buf;
    t_size capacity = BUFF_SIZE;

    while (1)
    {
       bytesread = read(fd, &c, 1); 

        if (bytesread < 1 || c == '\n')
        {
            break ;
        }
     
        capacity = check_update_mem_capacity(line, i, capacity);
        buf[i] = c;
        i++;
    }
    return 0;
}








