/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 10:28:27 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/02 11:10:44 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	if (ft_strlen(set) == 0 || end == 0)
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	while (ft_strchr(set, s1[end - 1]) && end)
		end--;
	if (end == 0)
		start = end;
	return (ft_substr(s1, start, end - start));
}
