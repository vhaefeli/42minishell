/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshorten.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:11:38 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/13 14:53:08 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function who realloc the correct memory when you shorten a str by puting a \0
// somwhere in the middle

char	*ft_strshorten(char *src)
{
	char	*shortstr;
	int		i;

	i = 0;
	shortstr = malloc(ft_strlen(src) + 1);
	while(src[i])
	{
		shortstr[i] = src[i];
		i++;
	}
	shortstr[i] = 0;
	//free(src);
	return (shortstr);
}
