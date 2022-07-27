/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/25 22:27:09 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "minishell.h"

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

int	ft_cntcmdline(char *s)
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

int	ft_cntchar(char *s, char c, int i)
{
	int	start;
	
	start = i;
	while (s[i] == ' ')
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i] == '\'')
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
