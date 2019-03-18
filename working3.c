#define BUFF_SIZE 13
#define MAX_FD  6048

#include "libft.h"
#include <stdio.h>
#include <fcntl.h> 

// int	next_line(char **str, char **line, int fd)
// {
// 	int		len;
// 	char	*basket;

// 	len = 0;
// 	while ((str[fd][len] != '\n') || (str[fd][len] != '\0'))		
// 	{
// 		len++;
// 	}
// 	if (str[fd][len] == '\n')
// 	{
// 		*line = ft_strsub(str[fd], 0, len);             //make substring(which strarts at 0 and ends before \n) from the file
// 		len = len + 1;                                  //go to the address after \n (this is gonna be where the new line starts)
// 		basket = ft_strdup(str[fd] + len);              //duplicate the rest of the string after \n and keep it in basket
// 		free(&str[fd]);                                 //erase from str[fd] because we have it in basket now
// 		str[fd] = basket;
// 		if (str[fd][0] == '\0')                         //in case the firs line of fd is has \n only
// 			free(&str[fd]);
// 	}
// 	else if (str[fd][len] == '\0')
// 	{
// 		*line = ft_strdup(str[fd]);
// 		free(&str[fd]);
// 	}
// 	return (1);
// }

// int get_next_line(const int fd, char **line)            //fd is ==  to 3 here
// {
// 	char	*temp;
// 	char	*str[MAX_FD];                               //if we need to read from different files for ex we have 100 files(they are strings)
// 	char	buff[BUFF_SIZE + 1];                        //our "basket" which can keep only 5 bytes(becase BUFF_SIZE is 5) + 1 for \0
// 	int		res;                                        //number of bytes we return after read()

// 	if (fd < 0 || fd > MAX_FD || line == NULL)
// 		return (-1);
// 	while ((res = read(fd, buff, BUFF_SIZE)) >= 0)      //while read doest return -1
// 	{
// 		buff[res] = '\0';                               //we took 5 bytes(characters) from file and creat the complet string
// 		str[fd] = ft_strnew(1);                         //we allocated memmory for second parameter of string join						
// 		temp = ft_strjoin(str[fd], buff);
// 		free(&str[fd]);                                 //we free() to erase everything inside the str[fd] and rewrite latter the result of new temp
// 		str[fd] = temp;                                 //rewrite the result of new temp
// 		if (ft_strchr(temp, '\n'))                      //fins \n in our string temp
// 			break;                                      //get out of the while loop if find new line
// 	}
// 	if (res == -1 || (res == 0 && (str[fd] == NULL || str[fd][0] == '\0'))) //in case of error (-1) || nothing to read ||fd is NULL || fd is empty
// 		return (res);
// 	//read from new line (the text after \n)
// 	return (next_line(str, line, fd));
// }


int next_line(char ** line, int fd, char ** file)
{
	int i = 0;
	printf(" res is %s\n", file[fd]);

	while (file[fd][i] != '\n' && file[fd][i] != '\0')
	{
		printf("i - %c\n", file[fd][i]);
		i++;
	}

	if (file[fd][i] == '\0')
	{
		*line = file[fd];
		//free(&file[fd]);
	}


	if (file[fd][i] == '\n')
	{
		*line = ft_strsub(file[fd], 0, i);
		i++;
		char * tmp = ft_strdup(file[fd] + i);
		//free(&file[fd]);
		file[fd] = tmp;
		if (file[fd][0] == '\0')
			free(&file[fd]);
 	}
 	return 1; 
}


struct File {
	int fd;
	char buff [BUFF_SIZE + 1] = {'\0'};
};

int get_next_line(const int fd, char **line)
{
	static char * file [4865];
	char buff [BUFF_SIZE + 1] = {'\0'};

	char * tmp;
	int res;

	if (fd < 0 || fd > 4864 || !line)
		return -1;


	while ((res = read(fd, buff, BUFF_SIZE)) > 0)
	{
		printf("buff is 		%s\n", buff);
		file[fd] = ft_strnew(0);


		tmp = ft_strjoin(file[fd], buff);

		printf("tmp is 		%s\n", tmp);
		//free(&file[fd]);
		file[fd] = tmp;
		printf("file[fd] is 		%s\n", file[fd]);


		if (ft_strchr(buff, '\n'))
			break;
		ft_bzero(buff, BUFF_SIZE + 1);

	}

	if (res == -1 || (res == 0 && (file[fd][0] == 0 || !file[fd])))
		return res;

	return (next_line(line, fd, file));
}


 int main(void)
{
    int fd = open("text.txt", O_RDONLY);
    char *line; 
    int status = get_next_line(fd, &line);
    printf("status - %d, Line is - \n%s\n\n", status, line);
    status = get_next_line(fd, &line);
    printf("status - %d, Line is - \n%s\n\n", status, line);
    status = get_next_line(fd, &line);
    printf("status - %d, Line is - \n%s\n\n", status, line);

    return 0;
}