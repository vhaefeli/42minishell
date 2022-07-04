/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:20:35 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/10/28 14:54:53 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cntline(const char *s, char c)
{
	size_t	i;
	size_t	nline;

	i = 0;
	nline = 0;
	if (s[0] != c)
		nline++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i] != '\0')
		{
			i++;
			nline++;
		}
		else if (s[i] != c && s[i + 1] == '\0')
		{
			nline++;
			i++;
		}
		else
			i++;
	}
	return (nline);
}

static size_t	ft_cntchar(const char *s, char c, size_t i)
{
	size_t	nchar;
	size_t	m;

	m = i;
	nchar = 0;
	while (s[m] == c)
		m++;
	while (s[m] != c && s[m] != '\0')
	{
		m++;
		nchar++;
	}
	return (nchar);
}

static char	**ft_filltab(const char *s, char c, char **dst)
{
	size_t	i;
	size_t	j;
	size_t	l;
	size_t	line;

	i = 0;
	j = 0;
	l = 0;
	line = ft_cntline(s, c);
	while (l + 1 < line)
	{
		dst[l] = (char *)malloc(ft_cntchar(s, c, i) + 1);
		if (!dst[l])
			return (NULL);
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			dst[l][j++] = s[i++];
		dst[l++][j] = '\0';
		j = 0;
		i++;
	}
	dst[l] = ((void *)0);
	return (dst);
}

char	**ft_split(const char *s, char c)
{
	char	**dst;
	size_t	line;

	if (!s)
		return (NULL);
	line = ft_cntline(s, c);
	dst = (char **)malloc(line * sizeof(char *));
	if (!dst)
		return (NULL);
	dst = ft_filltab(s, c, dst);
	return (dst);
}
