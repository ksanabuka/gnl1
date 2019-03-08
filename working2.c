#define BUFF_SIZE 5
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
	if (fd < 0 || fd > 255)
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

t_fdlist *find_create_fd(t_fdlist *head, unsigned int fd)
{
    t_fdlist * tmp;
    t_fdlist *newel;

    if (!head)
    {
        newel = ft_create_elem(fd);
        head = newel; 
        return newel;
    }

    tmp = head;
    while (tmp)
        {
            if (tmp->fd == fd)
                return tmp;
            else
                tmp = tmp->next;
        }
    
        newel = ft_create_elem(fd);
        newel->next = head;
        head = newel; 
        return newel; 
}

int read_line_from_struct_and_delit(int fd, char **line, t_fdlist * head)
    {
        int i = 0;
        int res;
        t_fdlist *ourfile = find_create_fd(head, fd);
        if (ourfile->content == '\0')
            return -1;
        while (ourfile->content[i] != '\n' && ourfile->content[i] != '\0')
        {
            i++;
        }
        if (ourfile->content[i] != '\n')
            res = 1;
        
        if (ourfile->content[i] != '\0')
            res = 0;

        ourfile->csize = ourfile->csize - i;
        * line = ft_strsub(ourfile->content, 0, i);
        if (!line)
            return -1;

        char * tmp = ft_strsub(ourfile->content, i, ft_strlen(ourfile->content)- ft_strlen(*line));
        char * tmp1 = ft_strnew(ourfile->csize);
        tmp = ft_strcpy(tmp1, tmp);
        ft_strdel(&tmp);
        ft_strdel(&ourfile->content);

        ourfile->content = tmp;

        return res;
    }

int  add_to_end(t_fdlist *file, char *buf)
{
    char * tmp;
    if ((file->csize + ft_strlen(buf)) > file->capacity)
    {
        tmp = ft_strnew((file->capacity + 1) * 2);
        tmp = ft_strcpy(tmp, file->content);
        ft_strdel(&file->content);
        tmp = ft_strcat(tmp, buf);
        file->content = tmp;
        return 1;
    }
    else 
    {
        file->content = ft_strncat(file->content, buf, BUFF_SIZE);
        return 1;
    }
    return 0;
} 

int read_from_file_into_struc(int fd, t_fdlist * file)
{
    int bytesread; 
    char * buf;
    char * tmp = "";
    int status;

   	buf = ft_strnew(BUFF_SIZE);
 	
 	while (1)
 	{
        ft_strclr(buf);
		bytesread = read(fd, buf, BUFF_SIZE);
 		if (bytesread <= 0)
 		{
            return 0;
        }

        if (ft_strchr(buf, '\n'))
        {
            status = add_to_end(file, buf);
            return 1;
        }

        status = add_to_end(file, buf);
 	}
    ft_strdel(&buf);
}

int get_next_line(const int fd, char **line)
{
    static t_fdlist * head = find_create_fd(fd);

    int malcheck = prepare(fd, &line);
    if (malcheck == -1)
 		return -1; 

    int status = read_line_from_struct_and_delit(fd, line, head);

    if (!*line)
        read_from_file_write_into_struc(fd);
        status = read_line_from_struct_and_delit(fd, line, head);

    return status;
     
}


int main (void)
{
    char ** line = 0;
    int fd = open("text.txt", O_RDONLY);
    int status = get_next_line(fd, line);
    printf("status: %d, string: %s", status, *line);
    return 0;
}

