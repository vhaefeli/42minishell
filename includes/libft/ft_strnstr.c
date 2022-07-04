/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:40:49 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/10/21 13:48:52 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	n;
	size_t	max;

	n = ft_strlen(needle);
	max = len;
	i = 0;
	if (*(needle) == '\0')
		return ((char *)haystack);
	while (max >= 1 && (ft_strlen(haystack + i) >= n))
	{
		j = 0;
		while (*(haystack + i + j) == *(needle + j) && ((i + j) < len))
		{
			j++;
			if (*(needle + j) == '\0')
				return ((char *)haystack + i);
		}
		i++;
		max--;
	}	
	return (NULL);
}
