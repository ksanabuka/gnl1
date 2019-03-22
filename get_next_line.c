#include  "get_next_line.h"

t_fdlist	*find_or_create(t_fdlist **list, const int fd)
{
	t_fdlist	*node;

	node = *list;
	while (node)
	{
		if (node->fd == (unsigned int)fd)
			return (node);
		node = node->next;
	}
	if (!(node = (t_fdlist *)malloc(sizeof(t_fdlist))))
        return 0;
	node->fd = (unsigned int)fd;
	node->buffer = NULL;
	node->next = *list;
	*list = node;
	return (node);
}

int index_nlc(char * nlcplus, char * buff)
{
    return (nlcplus - buff);
}


void swap_join_del(char ** tmp, char ** str, char ** buff)
{
    *tmp = *str;
    *str = ft_strjoin(*str, *buff);  
    free(&tmp);
 
}

char * returnnl_storebuf(t_fdlist *current, char * buffer)
{
    char    *tmp;
    char    *nlcplus;
    char    *readtextnl;
    char    *line; 
    size_t  size;
    
    line = ft_strnew(0);
    while (!(nlcplus = ft_strchr(buffer, '\n')))
    {
        tmp = line;
        line = ft_strjoin(tmp, buffer);
        free(tmp);

        if (!(size = read(current->fd, buffer, BUFF_SIZE)))
        {
            current->status = 1;
            return line;
        }
        buffer[size] = '\0';
    }
        
        readtextnl = ft_strsub(buffer, 0, (size_t)index_nlc(nlcplus, buffer));
        
        tmp = ft_strjoin(line, readtextnl);
        free(line);
        line = tmp;
        
        tmp = ft_strdup(buffer + index_nlc(nlcplus, buffer) + 1);
        free(current->buffer);
        current->buffer = tmp;

        return (line);

}


int get_next_line(const int fd, char **line)
{
   static t_fdlist *head = 0;

    t_fdlist *cur;

    //char buf[BUFF_SIZE + 1];

    char * buf = (char*)malloc(sizeof(char) * BUFF_SIZE + 1);

    size_t size;

    if (!(cur = find_or_create(&head, fd)))
        return -1;
    if (line == NULL || fd < 0 || fd > 6450)
        return -1;

    if (cur->buffer && ft_strlen(cur->buffer))
    {    
        ft_strcpy(buf, cur->buffer);
        // free(cur->buffer);
    }
    else
    {
        (size = read(fd, buf, BUFF_SIZE));
       // printf("fd  -   %d\n buffer -   %s\n buf_size -     %d\n", fd, buf, BUFF_SIZE);
        if (!size)
        {
            free(buf);
            return 0;
        }
        buf[size] = '\0';
    }
    *line = returnnl_storebuf(cur, buf);


    if (cur->status == 1)
    {
        free(buf);
        return (0);
    }
    else 
    {
        free(buf);
        return (1);
    }
}       


#include "get_next_line.h"
#include <fcntl.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
            system("leaks a.out");

    return 0; 
}