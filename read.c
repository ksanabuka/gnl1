#define BUFF_SIZE 32
#include "libft.h"
#include <stdio.h>
#include <fcntl.h> 


// typedef struct      s_list
// {
//     void            *content;
//     unsigned int    csize;
//     unsigned int    capacity;
//     struct s_list   *next;
// }                   t_file;


int check_update_mem_capacity(char *buf, unsigned int csize, unsigned int capacity)
{
    char * new;

    if (capacity - 1 == csize || (capacity < csize))
    {
                printf("4\n");

        capacity += BUFF_SIZE;
        new =  (char *)ft_memalloc(capacity);
        if (!new)
            return 0;
        new = ft_memmove(new, buf, ft_strlen(buf));
        
        *buf = new;
        ft_memdel((void**)new);


    }
    
    return capacity;
}

int get_next_line(const int fd, char **line)
{
    unsigned int capacity = BUFF_SIZE;

    int bytesread; 
    char *buf;
    buf =  (char *)ft_memalloc(capacity);
        if (!buf)
            return 0;


    //char ** p_buf;
    unsigned int i = 0;
    char c;
    line = &buf;

    while (1)
    {
           printf("1\n");

       bytesread = read(fd, &c, 1); 

        if (bytesread < 1 || c == '\n')
        {
                       printf("2\n");

            break ;
        }
     
        capacity = check_update_mem_capacity(line, i, capacity);
        buf[i] = c;
        i++;     
        printf("3\n");

    }
    return 0;
}


int main (int ac, char ** av)
{

    av = 0;
    ac = 0;

    int fd = open("text.txt", O_RDONLY);
   // char * str = "";
   char ** line;
    printf("%d\n", fd);




    int bytesread; 
    char *buf;
    unsigned int i = 0;
    char c;
    line = &buf;
    unsigned int capacity = BUFF_SIZE;

    while (1)
    {
           printf("1\n");

       bytesread = read(fd, &c, 1); 

        if (bytesread < 1 || c == '\n')
        {
            break ;
        }
     
        capacity = check_update_mem_capacity(line, i, capacity);
        buf[i] = c;
        i++;     
        printf("3\n");

    }





   //get_next_line((const int)fd, line);

   printf("%s\n", *line);
   return 0;
}







