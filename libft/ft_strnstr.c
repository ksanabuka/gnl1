/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:53:54 by obuksha           #+#    #+#             */
/*   Updated: 2019/02/06 10:54:33 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	n;
	size_t			len_little;

	if (*little == '\0')
		return (char*)(big);
	n = 0;
	len_little = ft_strlen(little);
	while (*big != '\0')
	{
		if (n + len_little > len)
			return (NULL);
		if (ft_strncmp(big, little, len_little) == 0)
			return (char*)(big);
		big++;
		n++;
	}
	return (NULL);
}
