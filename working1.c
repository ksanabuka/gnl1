#define BUFF_SIZE 5
#include "libft.h"
#include <stdio.h>
#include <fcntl.h> 

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

char *ft_copyuntil(char*dst, char *buf, int c)
{
	char * res = NULL;
	if (dst)
	{
		if (!buf || ft_strlen(buf) == 0)
		{
			res = (char *)malloc((sizeof(char) * (ft_strlen(dst) + 1)));
			if (!res)
				return 0;
			res = ft_strcpy(res, dst);
			return res;

		}
		int requiredLen;

		if (!ft_strchr(buf, c))
			requiredLen = ft_strlen(buf);

		else 
		{ 
			requiredLen = ft_strlen(buf) - ft_strlen(ft_strchr(buf, c));
		}

		if (requiredLen == 0)
		{
			res = (char *)malloc((sizeof(char) * (ft_strlen(dst) + 1)));
			if (!res)
				return 0;
			res = ft_strcpy(res, dst);
			return res;

		}
		else 	
			res = ft_strjoin(dst, ft_strsub(buf, 0, requiredLen));
	}
 	return res;
}


// #include <stdio.h>

// int main (int ac, char ** av)
// {
// 	ac = 0;
// 	av = 0;

// 	char * s1 = (char *)malloc((sizeof(char) * 11));
// 	char * s2 = (char *)malloc((sizeof(char) * 6));

// 	s1 = "0123456789";
// 	s2 = "";

//  	printf("%s\n",	ft_copyuntil(s1, s2, 48));
// 	return 0;
// }

// int get_next_line(const int fd, char **line)



//int find_correct_file(const int fd, )

int main (int ac, char ** av)
{

    av = 0;
    ac = 0;

    int fd = open("text.txt", O_RDONLY);
   	int bytesread; 
    char * buf;
    char * line;
	char * tmp = "";

   	buf = ft_strnew(BUFF_SIZE);

 	int malcheck = prepare(fd, &line);
 	
 	if (malcheck == -1)
 		return 0; 

 	

 	while (1)
 	{
		tmp = line; 
 		bytesread = read(fd, buf, BUFF_SIZE);
 		if (bytesread <= 0)
 			break;
		printf("buff: %s\n", buf);

 		line = ft_copyuntil(tmp, buf, '0');
		printf("line:  %s\n", line);

 	}
	 
}

   
//     printf("%d\n", fd);

// }