#define BUFF_SIZE 5
#include "libft.h"
#include <stdio.h>
#include <fcntl.h> 


// - створити елементи в структурі 
// - прочитати лінію з різних елементів
// - лініі - з текстом до нового рядку. нуьовий рядок. немає фд


  typedef  struct      s_mylist
{
    unsigned int    fd;
    char            *content;
    unsigned int    csize;
    unsigned int    capacity;
    struct s_mylist   *next;
}                   t_fdlist;


t_fdlist *ft_create_elem(unsigned int fd)
{
    t_fdlist * newel;
    if(!(newel =(t_fdlist*)malloc(sizeof(t_fdlist))))
        return (0);
    newel->fd = fd;
    newel->content = ft_strnew(BUFF_SIZE);
    if (!newel->content)
        return 0;
    newel->csize = 0;
    newel->capacity = BUFF_SIZE;
    newel->next = 0;
    return newel;
}

t_fdlist *find_create_fd(t_fdlist **head, unsigned int fd)
{
    t_fdlist * tmp;
    t_fdlist *newel;
    if (!head)
        return 0;
    if (!*head)
    {
        newel = ft_create_elem(fd);
        *head = newel; 
        return newel;
    }

    tmp = *head;
    while (tmp)
        {
            if (tmp->fd == fd)
                return tmp;
            else
                tmp = tmp->next;
        }
    
        newel = ft_create_elem(fd);
        newel->next = *head;
        *head = newel; 
        return newel; 
}


int main(void)
{
    t_fdlist ** head;
    t_fdlist * new;
    head = &new;

    // new = ft_create_elem(2);

    // printf("fd - %d,\n content - %s,\n csize - %d,\n capacity - %d\n", (*head)->fd, new->content, new->csize, new->capacity);
    
 
   t_fdlist * second = find_create_fd(head, 3);
    second = find_create_fd(head, 2);
    second = find_create_fd(head, 2);

    printf("fd - %d,\n content - %s,\n csize - %d,\n capacity - %d\n", (*head)->fd, (*head)->content, (*head)->csize, (*head)->capacity);
   printf("fd - %d,\n content - %s,\n csize - %d,\n capacity - %d\n", (*head)->next->fd, (*head)->next->content, (*head)->next->csize, (*head)->next->capacity);
   printf("fd - %d,\n content - %s,\n csize - %d,\n capacity - %d\n", second->fd, second->content, second->csize, second->capacity);

second = 0;


    return 0;
}






// int read_line_from_struct_and_delit(int fd, char **line, t_fdlist * head)
//     {
//         int i = 0;
//         int res;
//         t_fdlist *ourfile = find_create_fd(head, fd);
//         printf("here!%s\n", ourfile->content);
//         if (ourfile->content == '\0')
//             return -1;
//         while (ourfile->content[i] != '\n' && ourfile->content[i] != '\0')
//         {
//             i++;
//         }
//         if (ourfile->content[i] != '\n')
//             res = 1;
        
//         if (ourfile->content[i] != '\0')
//             res = 0;

//         ourfile->csize = ourfile->csize - i;
//         * line = ft_strsub(ourfile->content, 0, i);
//         if (!line)
//             return -1;

//         char * tmp = ft_strsub(ourfile->content, i, ft_strlen(ourfile->content)- ft_strlen(*line));
//         char * tmp1 = ft_strnew(ourfile->csize);
//         tmp = ft_strcpy(tmp1, tmp);
//         ft_strdel(&tmp);
//         ft_strdel(&ourfile->content);

//         ourfile->content = tmp;

//         return res;
//     }
