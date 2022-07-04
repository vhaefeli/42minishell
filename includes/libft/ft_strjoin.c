/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:00:04 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/02 11:35:32 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	char	*dst;
	size_t	lone;
	size_t	ltwo;

	if (!s1 || !s2)
		return (NULL);
	lone = ft_strlen(s1);
	ltwo = ft_strlen(s2);
	i = 0;
	dst = malloc(lone + ltwo + 1);
	if (!dst)
		return (NULL);
	while (i < lone)
	{
		dst[i] = s1[i];
		i++;
	}
	while (i < (lone + ltwo + 1))
	{
		dst[i] = s2[i - lone];
		i++;
	}
	return (dst);
}
