/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/01 16:50:32 by vhaefeli         ###   ########.fr       */
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
	while (s[i] != '\0' && i > -1)
	{
		if (s[i] == ' ' && s[i + 1] != ' ' && s[i] != '\0' && nline++)
			i++;
		else if (s[i] == '\'')
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
	return (i - start);
}

int	cntlastchar(char *s, char c)
{
	int	i;
	int	tmp;

	i = 0;
	while (s[i])
	{
		while (s[i] != c && s[i] != '\0')
		{
			if (s[i] == '\'')
				i += quotesize_incl(s, i, '\'');
			else if (s[i] == '\"')
				i += quotesize_incl(s, i, '\"');
			else
				i++;
		}
		if (s[i] == c)
		{
			tmp = i;
			i++;
		}
	}
	return (tmp);
}

int	cntchar_noquote(char *s, char c, int i)
{
	int	start;
	int	j;

	start = i;
	j = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i += quotesize_incl(s, i, '\'');
			j += 2;
		}
		else if (s[i] == '\"')
		{
			i += quotesize_incl(s, i, '\"');
			j += 2;
		}
		else
			i++;
	}
	return (i - start - j);
}

char	*cpycmdflag(t_varchar *listcmd, t_msvar *env)
{
	if (listcmd->str2)
	{
		free (listcmd->str2);
		listcmd->str2 = NULL;
	}
	while (listcmd->str[listcmd->i] == ' ')
		(listcmd->i)++;
	listcmd->str2 = ft_strdup(listcmd->str);
	if (!listcmd->str2)
		return (NULL);
	listcmd->j = 0;
	while (listcmd->str[listcmd->i] != ' ' && listcmd->str[listcmd->i] != '\0')
	{
		if (listcmd->str[listcmd->i] == '$'
			&& listcmd->str[listcmd->i + 1] != ' '
			&& listcmd->str[listcmd->i + 1] != 0)
			add_dollar_data(listcmd, env);
		else if (listcmd->str[listcmd->i] == '\''
			|| listcmd->str[listcmd->i] == '\"')
			cpy_text_noquote(listcmd, env);
		else
			listcmd->str2[listcmd->j++] = listcmd->str[listcmd->i++];
	}
	listcmd->str2[listcmd->j] = '\0';
	return (ft_strshorten(listcmd->str2));
}
