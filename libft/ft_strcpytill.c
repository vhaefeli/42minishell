/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpytill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:12:21 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/11 17:13:49 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcpytill(char *src, int c)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(c + 1);
	while (i < c)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}