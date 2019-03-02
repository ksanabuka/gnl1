
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#ifndef BUFF_SIZE
#define BUFF_SIZE 32
#endif
#include "libft.h"
//reading from file;

// int main(void)
// {

// int fd, bytesread;


// char buf[BUFF] = {'\0'};


// fd = open("Gnl2.txt", O_RDONLY);


// if (fd < 0)
// {
//     perror("Error");
//     exit(1);
// }

// int i = 0;
// char c;

// while (1)
// {
//     bytesread = read(fd, &c, 1); 
//     printf("%d - 1\n", i);


//     if (c == '\n' || bytesread < 1 || i > size - 1)
//     {
//     	printf("%d - 2\n", i);
//         break ;
//     }

//     buf[i] = c;
//     printf("%d - 3\n", i);

//     i++;
// }

// buf[size - 1] = '\0';
// printf("%s\n %d\n", buf, bytesread);
// return 0;

// }

// reading from stdin




int main(void)
{

int myfd = 0, bytesread; 

char *buf;
char ** p_buf;



int i = 0;
char c;
unsigned int capacity = 2;
buf = (char *)ft_memalloc(sizeof(char)*capacity);
*p_buf = buf;

while (1)
{
   bytesread = read(myfd, &c, 1); 

    if (bytesread < 1 || i > BUFF_SIZE - 1)
    {
    	printf("exit - char %c, i - %d\n", c, i);
        break ;
    }
 
    
    capacity = check_update_mem_capacity(p_buf, i, capacity);
    buf[i] = c;
    printf("write - char %c, i - %d\n", c, i);
    i++;
}

buf[BUFF_SIZE] = '\0';
printf("%s\n", buf);
return 0;

}

int check_update_mem_capacity(char **p_buf, unsigned int csize, unsigned int capacity)
{
    char * new;

    if (capacity == csize - 1)
    {
        capacity = capacity * 2;
        new =  (char *)ft_memalloc(capacity);
        if (!new)
            return 0;
        new = ft_memmove(new, *p_buf, ft_strlen(p_buf));
        ft_memdel(p_buf);
        *p_buf = new;
    }
    
    return capacity;
}








