/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/13 14:53:13 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cntcmdline(char *s)
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
		else if (s[i] == '\''  )
			i += quotesize_incl(s, i, '\'');
		else if (s[i] == '\"')
			i += quotesize_incl(s, i, '\"');
		else
			i++;
		if (s[i] == '\0')
		nline++;
	}
	if (i < 0)
		return (0);
	return (nline);
}

int	cntchar(char *s, char c, int i)
{
	int	start;

	start = i;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'')
			i += quotesize_incl(s, i, '\'');
		else if (s[i] == '\"')
			i += quotesize_incl(s, i, '\"');
		else
			i++;
	}
	// printf("cntchar: %d\n", i - start);
	return (i - start);
}

int	cntchar_noquote(char *s, char c, int i)
{
	int	start;
	int j;

	start = i;
	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i += quotesize_incl(s, i, '\'');
			j+= 2;
		}
		else if (s[i] == '\"')
		{
			i += quotesize_incl(s, i, '\"');
			j+= 2;
		}
		else
			i++;
	}
	// printf("cntchar: %d\n", i - start - j);
	return (i - start - j);
}



char	*cpycmdflag(t_varchar *listcmd, t_msvar *env)
{
	if (listcmd->str2)
	{
		printf("str2: %s %p\n", listcmd->str2, listcmd->str2);
		free (listcmd->str2);
		listcmd->str2 = NULL;
	}
	while (listcmd->str[listcmd->i] == ' ')
		(listcmd->i)++;
	// linesize = cntchar_noquote(listcmd->str, ' ', listcmd->i);
	// listcmd->str2 = (char *)malloc(linesize * sizeof(char) + 1);
	listcmd->str2 = ft_strdup(listcmd->str);
	if (!listcmd->str2)
		return (NULL);
	listcmd->j = 0;
	while (listcmd->str[listcmd->i] != ' ' && listcmd->str[listcmd->i] != '\0')
	{
		if (listcmd->str[listcmd->i] == '$')
				add_dollar_data(listcmd, env);
		else if (listcmd->str[listcmd->i] == '\'' || listcmd->str[listcmd->i] == '\"')
			cpy_text_noquote(listcmd, env);
		else
			listcmd->str2[listcmd->j++] = listcmd->str[listcmd->i++];
	}
	listcmd->str2[listcmd->j] = '\0';
	printf("listcmd2-%s-\n", listcmd->str2);
	return (ft_strshorten(listcmd->str2));
}
