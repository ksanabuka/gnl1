
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

char buf[BUFF_SIZE + 1] = {'\0'};

int i = 0;
char c;

while (1)
{
   bytesread = read(myfd, &c, 1); 

    if (bytesread < 1 || i > BUFF_SIZE - 1)
    {
    	printf("exit - char %c, i - %d\n", c, i);
        break ;
    }

    buf[i] = c;
    printf("write - char %c, i - %d\n", c, i);
    i++;
}

buf[BUFF_SIZE] = '\0';
printf("%s\n", buf);
return 0;

}


// int capacity = 2;

// if (capacity == size - 1)
// {
//     new = malloc(capacity * 2);
//     memmove(old, new, sizeof(old));
// }







