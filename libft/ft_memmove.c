/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:06:42 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/10/22 11:19:02 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	void	*temp;

	temp = dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (temp);
	if ((dst - src) > 0 && (dst - src) < (long)len)
	{	
		while (i < len)
		{
			*((char *)(dst-- + len - 1)) = *((char *)(src-- + len - 1));
			i++;
		}
	}
	else
	{	
		while (i < len)
		{
			*(char *)dst++ = *(char *)src++;
			i++;
		}
	}
	return (temp);
}	
