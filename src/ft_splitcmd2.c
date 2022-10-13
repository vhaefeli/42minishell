/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/13 15:48:57 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**filltab(char *s, int nbline, t_msvar *env)
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

	// printf("nbline:%d", nbline);
	dst = malloc(sizeof(char *) * nbline);
	while (l < nbline - 1)
	{
		dst[l] = cpycmdflag(lignecmd, env);
		printf("Adst[0]:%s-\n", dst[0]);
		printf("dst[%d]:%p\n", l, dst[l]);
		l++;
		// printf"i: %d\n", lignecmd->i);
	}
	// printf("l:%d\n", l);
	dst[l] = NULL;
	// free (lignecmd->str2);
	// free (lignecmd);
	// printf("Adst[0]:%p-\n", dst[0]);
	// printf("Adst[1]:%p-\n", dst[1]);
	return (dst);
}

char	**ft_splitcmd(char *s, t_msvar *env)
{
	char	**dst;
	size_t	line;

	if (!s)
		return (NULL);
	line = cntcmdline(s);
	// printf("line:%zu\n", line);
	dst = (char **)malloc(line * sizeof(char *));
	if (!dst)
		return (NULL);
	dst = filltab(s, line, env);
	printf("dst[0]:%s-\n", dst[0]);
	printf("dst[1]:%s-\n", dst[1]);
	return (dst);
}

