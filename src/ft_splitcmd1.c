/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitcmd1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 18:54:15 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/05 21:56:18 by vhaefeli         ###   ########.fr       */
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
		else if (s[i] != ' ' && s[i + 1] == '\0' && nline++)
			i++;
		else if (s[i] == '\''  )
			i += quotesize_incl(s, i, '\'');
		else if (s[i] == '\"')
			i += quotesize_incl(s, i, '\"');
		else
			i++;
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

// void	ft_writequote(t_varchar *listcmd, int j)
// {
// 		if (listcmd->str[listcmd->i] == '\'')
// 		{
// 			// listcmd->str2[listcmd->i - j] = '\'';
// 			(listcmd->i)++;
// 			while (listcmd->str[listcmd->i] != '\'')
// 			{
// 				listcmd->str2[listcmd->i - j] = listcmd->str[listcmd->i];
// 				(listcmd->i)++;
// 			}
// 			// listcmd->str2[listcmd->i - j] = '\'';
// 			(listcmd->i)++;
// 		}
// 		else if (listcmd->str[listcmd->i] == '\"')
// 		{
// 			// listcmd->str2[listcmd->i - j] = '\"';
// 			(listcmd->i)++;
// 			while (listcmd->str[listcmd->i] != '\"')
// 			{
// 				listcmd->str2[listcmd->i - j] = listcmd->str[(listcmd->i)];
// 				(listcmd->i)++;
// 			}
// 			// listcmd->str2[listcmd->i - j] = '\"';
// 			(listcmd->i)++;
// 		}
// }

char	*cpycmdflag(t_varchar *listcmd)
{
	int		linesize;

	if (listcmd->str2)
	{
		free (listcmd->str2);
		listcmd->str2 = NULL;
	}
	while (listcmd->str[listcmd->i] == ' ')
		(listcmd->i)++;
	linesize = cntchar_noquote(listcmd->str, ' ', listcmd->i);
	listcmd->str2 = (char *)malloc(linesize * sizeof(char) + 1);
	if (!listcmd->str2 || linesize == 0)
		return (NULL);
	listcmd->j = 0;
	while (listcmd->str[listcmd->i] != ' ' && listcmd->str[listcmd->i] != '\0')
	{
		if (listcmd->str[listcmd->i] == '\'' || listcmd->str[listcmd->i] == '\"')
			cpy_text_noquote(listcmd);
		else
			listcmd->str2[listcmd->j++] = listcmd->str[listcmd->i++];
	}
	listcmd->str2[listcmd->j] = '\0';
	// printf("listcmd2-%s-\n", listcmd->str2);
	return (listcmd->str2);
}
