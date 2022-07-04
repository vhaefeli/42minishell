/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:55:14 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/10/22 11:25:53 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	sizedst;
	size_t	sizesrc;

	sizedst = ft_strlen(dst);
	sizesrc = ft_strlen(src);
	if (dstsize == 0 || sizedst >= dstsize)
		return (sizesrc + dstsize);
	while (*dst != '\0' && --dstsize > 0)
		dst++;
	while (*src != '\0' && --dstsize > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (sizedst + sizesrc);
}
