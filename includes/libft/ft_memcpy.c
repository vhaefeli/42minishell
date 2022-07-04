/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:43:13 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/10/21 17:36:06 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	void	*temp;

	temp = dst;
	i = 0;
	if (dst == 0 && src == 0)
		return (temp);
	while (i < n)
	{
		*(char *)dst++ = *(char *)src++;
		i++;
	}
	return (temp);
}	
