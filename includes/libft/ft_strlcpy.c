/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:30:33 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/10/22 11:27:38 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	sizesrc;

	sizesrc = ft_strlen(src);
	if (dstsize == 0)
		return (sizesrc);
	while (*src != '\0' && --dstsize > 0)
		*dst++ = *src++;
	*dst = '\0';
	return (sizesrc);
}
