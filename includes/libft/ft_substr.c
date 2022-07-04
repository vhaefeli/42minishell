/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:01:38 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/02 11:35:10 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
	{
		dst = malloc (0);
		*dst = '\0';
		return (dst);
	}
	else if (len < (ft_strlen(s) + 1 - start))
		dst = malloc(len + 1);
	else
		dst = malloc(ft_strlen(s) + 1 - start);
	if (!dst)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		dst[i] = s[i + start];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
