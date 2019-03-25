/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:00:29 by obuksha           #+#    #+#             */
/*   Updated: 2019/03/25 10:00:37 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 50

# include <stdlib.h>
# include "libft/libft.h"

typedef struct		s_mylist
{
	int				fd;
	char			*buffer;
	struct s_mylist	*next;
}					t_fdlist;

int					get_next_line(const int fd, char **line);

#endif
