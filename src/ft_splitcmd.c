/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/14 20:05:17 by vhaefeli         ###   ########.fr       */
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

typedef	struct s_varchar
{
	int		i;
	int		j;
	char	*str;
	char	*str2;
} t_varchar;

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	i = 0;
	copy = malloc(strlen(s1) + 1);
	printf("strlen: %lu\n", strlen(s1));
	if (!copy)
		return (NULL);
	while (s1[i] != '\0')
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	printf("copy: %s\n", copy);
	return (copy);
}

int	quotesize(char *s, int i, char quotetype)
{
	int	quotesize;
	int	j;

	quotesize = 2;
	j = i;
	i++;
	while(s[i] != quotetype && s[i] != '\0')
	{
		i++;
		quotesize++;
		if (s[i] == '\0')
		{
			printf("error : you can have only an even number of %c quotes\n", quotetype);
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
			i += quotesize(s, i, '\'');
		else if (s[i] == '\"')
			i += quotesize(s, i, '\"');
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
			i += quotesize(s, i, '\'');
		else if (s[i] == '\"')
			i += quotesize(s, i, '\"');
		else
			i++;
	}
	return (i - start);
}

void	ft_writequote(t_varchar *listcmd, int j)
{
		if (listcmd->str[listcmd->i] == '\'')
		{
			listcmd->str2[listcmd->i - j] = '\'';
			(listcmd->i)++;
			while (listcmd->str[listcmd->i] != '\'')
			{
				listcmd->str2[listcmd->i - j] = listcmd->str[listcmd->i];
				(listcmd->i)++;
			}
			listcmd->str2[listcmd->i - j] = '\'';
			(listcmd->i)++;
		}
		else if (listcmd->str[listcmd->i] == '\"')
		{
			listcmd->str2[listcmd->i - j] = '\"';
			(listcmd->i)++;
			while (listcmd->str[listcmd->i] != '\"')
			{
				listcmd->str2[listcmd->i - j] = listcmd->str[(listcmd->i)];
				(listcmd->i)++;
			}
			listcmd->str2[listcmd->i - j] = '\"';
			(listcmd->i)++;
		}
}

char	*cpycmdflag(t_varchar *listcmd)
{
	
	int		j;
	int		linesize;

	if (listcmd->str2)
		free (listcmd->str2);
	linesize = ft_cntchar(listcmd->str, listcmd->i);
	listcmd->str2 = (char *)malloc(linesize * sizeof(char));
	if (!listcmd->str2 || linesize == 0)
		return (NULL);
	while (listcmd->str[listcmd->i] == ' ')
		(listcmd->i)++;
	j = listcmd->i;
	while (listcmd->str[listcmd->i] != ' ' && listcmd->str[listcmd->i] != '\0')
	{
		if (listcmd->str[listcmd->i] == '\'' || listcmd->str[listcmd->i] == '\"')
			ft_writequote(listcmd, j);
		else
		{
			listcmd->str2[listcmd->i - j] = listcmd->str[listcmd->i];
			(listcmd->i)++;
		}
	}
	listcmd->str2[listcmd->i - j] = '\0';
	return (listcmd->str2);
}

static char	**ft_filltab(char *s, int nbline)
{
	t_varchar	*lignecmd;
	int			l;
	char		**dst;

	lignecmd = malloc (sizeof(t_varchar));
	lignecmd->str = s;
	lignecmd->i = 0;
	l = 0;
	dst = malloc(sizeof(char *) * nbline);
	while (l < nbline - 1)
	{
		dst[l] = ft_strdup(cpycmdflag(lignecmd));
		l++;
	}
	dst[l] = NULL;
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
	dst = ft_filltab(s, line);
	return (dst);
}

int	main(int argc, char **argv)
{
	char	**tab;
	int	i = 0;
	char *src;

	src = argv[argc - 1];
	// printf("str : %s\n", src);
	// printf("argc:%d\n", argc);
	// printf("nbre de commande %d\n", ft_cntcmdline(src) - 1);
	tab = ft_splitcmd(src);
	while (tab[i])
	{
		printf("cmd:%s\n", tab[i]);
		i++;
	}
	return (0);
} 