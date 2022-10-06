/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/06 15:08:49 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**filltab(char *s, int nbline)
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
		// printf"i: %d\n", lignecmd->i);
	}
	dst[l] = NULL;
	free (lignecmd->str2);
	free (lignecmd);
	return (dst);
}

char	**ft_splitcmd(char *s)
{
	char	**dst;
	size_t	line;

	if (!s)
		return (NULL);
	line = cntcmdline(s);
	printf("line:%zu\n", line);
	dst = (char **)malloc(line * sizeof(char *));
	if (!dst)
		return (NULL);
	dst = filltab(s, line);
	return (dst);
}

