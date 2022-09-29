/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/09/29 13:08:02 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
size_t	size_between_spaces(char *s, int i)
{
	int	j;

	j = 0;
	while (s[i] == ' ')
		i++;
	printf("size_between_spaces2 c: %c\n", s[i]);
	while (s[i] != ' ' && s[i] != 0)
	{
		printf("size_between_spaces3 c: %c\n", s[i]);
		if (s[i] == '\'')
		{
			j += quotesize(s, i, '\'');
			i += quotesize(s, i,  '\'') + 2;
		}
		else if (s[i] == '\"')
		{
			j += quotesize(s, i, '\"');
			i += quotesize(s, i, '\"') + 2;
		}
		else
		{
			i++;
			j++;
		}
		printf("size_between_spaces c: %c\n", s[i]);
	}
	return (j);
}

char	**ft_filltab(char *s, int nbline)
{
	t_varchar	*lignecmd;
	int			l;
	char		**dst;

	lignecmd = malloc (sizeof(t_varchar));
	lignecmd->str = s;
	lignecmd->str2 = NULL;
	lignecmd->i = 0;
	lignecmd->j = 0;
	l = 0;
	dst = malloc(sizeof(char *) * nbline);
	while (l < nbline - 1)
	{
		dst[l] = ft_strdup(cpycmdflag(lignecmd));
		l++;
	}
	dst[l] = NULL;
	free (lignecmd->str2);
	free (lignecmd);
	// int		i;
	// int		j;
	// size_t	cmdsize;
	// char	*cmdflag;

	// i = 0;
	// j = 0;
	// cmdsize = size_between_spaces(cmdline, i) + 1;
	// cmdflag = malloc(cmdsize);
	// while (cmdsize--)
	// {
	// 	if (s[i] !=
	// 	cmdflag[j] =
	// }



	return (dst);
}

char	**ft_splitcmd(char *s)
{
	char	**dst;
	size_t	line;

	if (!s)
		return (NULL);
	line = ft_cntcmdline(s);
	printf("line:%zu\n", line);
	dst = (char **)malloc(line * sizeof(char *));
	if (!dst)
		return (NULL);
	dst = ft_filltab(s, line);
	return (dst);
}

