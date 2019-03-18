#define BUFF_SIZE 10
#include "libft.h"
#include <stdio.h>
#include <fcntl.h> 


  typedef  struct      s_mylist
{
    unsigned int    fd;
    char            *content;
    unsigned int    csize;
    unsigned int    capacity;
    struct s_mylist   *next;
}                   t_fdlist;


int prepare (const int fd, char **line)
{
    if (fd < 0)
        return (-1);
    if (line == NULL)
        return (-1);
    *line = ft_strnew(1);
    if(*line == NULL)
        return (-1);
    return (0);
}

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

#include <stdio.h>

int  add_to_end(t_fdlist *file, char *buf)
{
    char * tmp;
    if ((file->csize + ft_strlen(buf)) >= file->capacity)
    {
        tmp = ft_strnew((file->capacity) * 2);
        tmp = ft_strcpy(tmp, file->content);
        ft_strdel(&file->content);
        tmp = ft_strcat(tmp, buf);
        file->content = tmp;
        file->capacity = file->capacity * 2;
        file->csize = file->csize + ft_strlen(buf);
        return 1;
    }
    else 
    {
        file->content = ft_strncat(file->content, buf, BUFF_SIZE);
        file->csize = file->csize + ft_strlen(buf);

        return 1;
    }
    return 0;
} 
int d = 0;
int read_from_file_into_struc(int fd, t_fdlist ** head)
{
    int bytesread; 
    char * buf;
    int status;
    t_fdlist * file = find_create_fd(head, fd);

    buf = ft_strnew(BUFF_SIZE);
    int flag = 0;
    while (1)
    {
      //  printf("%d in circle - %s\n", d, file->content);

        ft_strclr(buf);
        bytesread = read(fd, buf, BUFF_SIZE);
        if (bytesread < 0 || (bytesread == 0  && flag == 0))
        {
         //   printf("all string in file - %s\n", file->content);

            return -1;
        }
        if (bytesread == 0 && flag == 1)
        {
          //  printf("all string in file - %s\n", file->content);

            return 1;
        }
        char * tmp = buf;
        if (ft_strchr(tmp, '\n'))
        {
            status = add_to_end(file, buf);
           // printf("Newlinesign file->c - %s\n", file->content);

            return 1;
        }

        status = add_to_end(file, buf);
        flag = 1;
        d++;

    }
    ft_strdel(&buf);
    
}


int read_line_from_struct_and_delit(int fd, char **line, t_fdlist ** head)
    {
        int i = 0;
        t_fdlist *ourfile = find_create_fd(head, fd);
        if (ourfile->content[i] == '\0')
            return -1;
        if (ourfile->content[i] == '\n')
        {
            i++;
        }
        while (ourfile->content[i] != '\n' && ourfile->content[i] != '\0')
        {
            i++;
        }
        // if (ourfile->content[i] == '\n')
        // {   
        //     i++;
        // }

        if (ourfile->content[i] == '\0')
        {
            *line = ourfile->content;
            return 0;
        }

        else //  ourfile->content[i] == '\n'
        {
            //printf("!!!!%s\n", ourfile->content);
           *line = ft_strsub(ourfile->content, 0, i);

            if (!line)
                return -1;


           i++;
            if (ourfile->content[i] == '\0')
            {
              //free(&ourfile->content);
                return -2;
            }



            char * rest = ft_strdup(ourfile->content + i);

            //ft_strdel(&ourfile->content);

            ourfile->content = rest;
            ourfile->csize = ourfile->csize - i;
          //  char * ourfil = ourfile->content;
            //printf("ourfile %s\n",  ourfil);

            return 1;
        }
    }


int get_next_line(const int fd, char **line)
{
    static t_fdlist *head;
    //*line = 0;

    t_fdlist * firstel;
    firstel = find_create_fd(&head, fd);
    
    int malcheck = prepare(fd, line);
    if (malcheck == -1)
        return -1; 

    int  status = read_from_file_into_struc(fd, &head);

    if (status <= 0)
        return (-1);

    status = read_line_from_struct_and_delit(fd, line, &head);

    // if (status == -1 || status == -2 || status == 0)
    // {
    //     status = read_from_file_into_struc(fd, &head);
    //     status = read_line_from_struct_and_delit(fd, line, &head);
    // }
    return status;

}


 int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *line; 
    
   // int status = 0;

    while (get_next_line(fd, &line) >= 0)
    {
        printf("%s\n", line);
    }
   
    return 0;
}

