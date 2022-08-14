/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpyfrom.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:00:28 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/11 17:13:46 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpyfrom(char *src, int c)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(ft_strlen(src) - c + 1);
	while (src[c + i] != '\0')
	{
		dst[i] = src[c + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
