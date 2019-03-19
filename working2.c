#define BUFF_SIZE 100
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
      printf("%d in circle - '%s'\n", d, file->content);

        ft_strclr(buf);
        bytesread = read(fd, buf, BUFF_SIZE);
        if (bytesread < 0)
        {
            printf("read Eror! all string in file - '%s'\n", file->content);

            return -1;
        }


        if ((bytesread == 0  && flag == 0))
        {
            printf("READ Eror! all string in file - '%s'\n", file->content);

            return -6;
        }


        if (bytesread == 0 && flag == 1)
        {
          printf("read=0,flag=1 - '%s'\n", file->content);

            return -5;
        }
        char * tmp = buf;
        if (ft_strchr(tmp, '\n'))
        {
            if ((ft_strchr(tmp, '\n') && ft_strlen(tmp) == 1))
            {
                status = add_to_end(file, buf);
                printf("/n && bufflen=1    file->c - '%s'\n", file->content);

            return 1;
            }
           else 
            {
                status = add_to_end(file, buf);
                printf("/n   file->c - '%s'\n", file->content);
                flag = 1;

                return 2;
            }
        }
        status = add_to_end(file, buf);
        flag = 1;
        printf("%d End circle - '%s'\n\n", d, file->content);
        d++;



    }
    ft_strdel(&buf);
    
    printf("%d at end of reading - '%s'\n\n", d, file->content);
    
}


int read_line_from_struct_and_delit(int fd, char **line, t_fdlist ** head)
    {
        int i = 0;
        char * rest;
        t_fdlist *ourfile = find_create_fd(head, fd);
        
        
        if (ourfile->content[i] == '\0')
            return -1;
       

        if (ourfile->content[i] == '\n')
        {
                *line = ft_strnew(0);
                i++;
                rest = ft_strdup(&ourfile->content[i]);
                //ft_strdel(&ourfile->content);

                ourfile->content = rest;
                ourfile->csize = ourfile->csize - i;

                if (ourfile->content[i + 1] == '\0')
                            {
                            //free(&ourfile->content);
                                return -3;
                            }
        
                return -2;
        }



       while (ourfile->content[i] != '\n' && ourfile->content[i] != '\0')
        {
            i++;
        }
        

        if (ourfile->content[i] == '\0')
        {
           *line = ft_strsub(ourfile->content, 0, i);
            rest = ft_strnew(0);

            //ft_strdel(&ourfile->content);

            ourfile->content = rest;
            ourfile->csize = ourfile->csize - i;
       
        return -4;
        }

        if (ourfile->content[i] == '\n')
        {
           *line = ft_strsub(ourfile->content, 0, i);
            rest = ft_strdup(ourfile->content + i + 1);

            //ft_strdel(&ourfile->content);

            ourfile->content = rest;
            ourfile->csize = ourfile->csize - i - 1;
            
            if (ourfile->content[i + 1] && ourfile->content[i + 1] == '\0')
            {
              //free(&ourfile->content);
                return -6;
            }     
       
        return -5;
        }

        return 1;

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

    if (status == -6 || status == -1 ) && file->content[0] == '\0')
        return (-1);

    if (status == -5)       
    { 
        status = read_line_from_struct_and_delit(fd, line, &head);
        printf("st - %d\n", status);

        status = 0;
        return status;
    }

        status = read_line_from_struct_and_delit(fd, line, &head);
        printf("st - %d\n", status);

        status = 1;
        return status;

}


 int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *line; 
    
   int status = 0;
   int i = 0;

    //while (i < 10)
    while (status >= 0)
    {

        (status = get_next_line(fd, &line));
       // printf("'%s'\n", line);

        printf("status %d  -   LINE -   '%s'\n\n\n", status, line);
        i++;
    }
   
    return 0;
}

