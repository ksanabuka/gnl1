#define BUFF_SIZE 32
#include "libft.h"
#include <stdio.h>
#include <fcntl.h> 


// 	typedef struct      s_list
// {
//     void            *content;
//     unsigned int    csize;
//     unsigned int    capacity;
//     struct s_list   *next;
// }                   t_file;

char *ft_copyuntil(char*dst, char *buf, int c)
{
	if (!buf || ft_strlen(buf) == 0)
		return dst;

	int requiredLen = ft_strlen(buf) - ft_strlen(ft_strchr(buf, c));
	if (requiredLen == 0)
		return dst;
	char * res = ft_strjoin(dst, ft_strsub(buf, 0, requiredLen));
	ft_strdel(&dst);
	ft_strclr(buf);
	return res;
}

// #include <stdio.h>

// int main (int ac, char ** av)
// {
// 	ac = 0;
// 	printf("%s\n", ft_copyuntil(av[1], av[2], 48));
// 	return 0;
// }

//int get_next_line(const int fd, char **line)

int prepare (const int fd, char **line)
{
	if (fd < 0 || fd > 255)
		return (-1);
	if (line == NULL)
		return (-1);
	*line = ft_strnew(0);
	if(*line == NULL)
		return (-1);
	return (0);
}

//int find_correct_file(const int fd, )

int main (int ac, char ** av)
{

    av = 0;
    ac = 0;

    int fd = open("text.txt", O_RDONLY);
   

	int bytesread; 
    char * buf;
    char * tmp;
   buf = ft_strnew(BUFF_SIZE);


	char ** line = &tmp;

 	int malcheck = prepare(fd, line);
 	
 	if (malcheck == -1)
 		return 0; 

 	

 	while (1)
 	{

 		bytesread = read(fd, &buf, BUFF_SIZE);
 		if (bytesread <= 0)
 			break;
 		tmp = ft_copyuntil(*line, buf, 48);
 		line = &tmp;


 	}}

   
//     printf("%d\n", fd);

// }