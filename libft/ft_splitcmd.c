/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/13 20:41:29 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// include "minishell.h"
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

int	quotesize(char *s, int i, char *quotetype)
{
	int	quotesize;
	int	j;

	quotesize = 2;
	j = i;
	i++;
	while(s[i] != '\'' && s[i] != '\0')
	{
		i++;
		quotesize++;
		if (s[i] == '\0')
		{
			printf("error : you can have only an even number of %s quotes", quotetype);
			return (- j - 1);
		}
	}
	return (quotesize);
}

static int	ft_cntcmdline(char *s)
{
	int	i;
	int	nline;

	i = 0;
	nline = 0;
	if (s[0] != ' ')
		nline++;
	while (s[i] != '\0' && i > - 1)
	{
		if (s[i] == ' ' && s[i + 1] != ' ' && s[i] != '\0' && nline++)
			i++;
		else if (s[i] != ' ' && s[i + 1] == '\0' && nline++)
			i++;
		else if (s[i] == '\''  )
			i += quotesize(s, i, "single quote");
		else if (s[i] == '\"')
			i += quotesize(s, i, "double quote");
		else
			i++;
	}
	if (i < 0)
		return (0);
	return (nline);
}

static int	ft_cntchar(char *s, int i)
{
	int	start;
	
	start = i;
	while (s[i] == ' ')
		i++;
	while (s[i] != ' ' && s[i] != '\0')
	{
		if (s[i] == '\''  )
			i += quotesize(s, i, "single quote");
		else if (s[i] == '\"')
			i += quotesize(s, i, "double quote");
		else
			i++;
	}
	return (i - start);
}

void	ft_writequote(char *s, char **flag, int *i, int j)
{
		if (s[*i] == '\'')
		{
			*flag[*i - j] = '\'';
			i++;
			while (s[*i] != '\'')
				*flag[*i - j] = s[*i++];
			*flag[*i - j] = '\'';
			*i++;
		}
		else if (s[*i] == '\"')
		{
			*flag[*i - j] = '\"';
			i++;
			while (s[*i] != '\"')
				*flag[*i - j] = s[*i++];
			*flag[*i - j] = '\"';
			*i++;
		}
}

char	*cpycmdflag(char *s, int *i)
{
	char	*flag;
	int		j;

	j = *i;
	flag = (char *)malloc(ft_cntchar(s, *i));
	if (!flag)
		return (NULL);
	while (s[*i] == ' ')
		*i++;
	while (s[*i] != ' ' && s[*i] != '\0')
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			ft_writequote(s, &flag, i, j);
		else
		{
			flag[*i - j] = s[*i];
			*i++;
		}
	}
	flag[*i - j] = '\0';
	return (flag);
}

static char	**ft_filltab(char *s)
{
	int		i;
	int		l;
	int		line;
	char	**dst;

	i = 0;
	l = 0;
	line = ft_cntcmdline(s);
	while (l < line)
	{
		printf("i: %d\n", i);
		dst[l] = cpycmdflag(s, &i);
		l++;
	}
	dst[l] = (NULL);
	return (dst);
}

char	**ft_splitcmd(char *s)
{
	char	**dst;
	size_t	line;

	if (!s)
		return (NULL);
	line = ft_cntcmdline(s);
	dst = (char **)malloc(line * sizeof(char *));
	if (!dst)
		return (NULL);
	dst = ft_filltab(s);
	return (dst);
}

int	main(int argc, char **argv)
{
	char	**tab;

	tab = ft_splitcmd(argv[1]);
	printf("%s\n", argv[argc - 1]);
	printf("argc:%d\n", argc);
	printf("%zu\n", ft_cntcmdline(argv[argc - 1]));
	while (*tab)
	{
		printf("cmd:%s\n", *tab);
		*tab++;
	}
	return (0);
} 