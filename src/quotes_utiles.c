/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:49:48 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/09 11:28:15 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checkquotes(char *s)
{
	int		i;
	char	quotetype;

	i = 0;
	quotetype = '\0';
	while (s[i])
	{
		while (s[i] && s[i] != '\'' && s[i] != '\"')
			i++;
		if (s[i])
			quotetype = s[i++];
		else
			return (0);
		while (s[i] != quotetype && s[i] != '\0')
		{
			i++;
			if (s[i] == '\0')
			{
				printf("error : you can have only an even nbr of quote\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	quotesize_incl(char *s, int i, char quotetype)
{
	int	quotesize;
	int	j;

	quotesize = 0;
	j = i;
	i++;
	while (s[i] != quotetype && s[i] != '\0')
	{
		i++;
		quotesize++;
		if (s[i] == '\0')
		{
			printf("error : you can have only an even ");
			printf("number of %c quotes\n", quotetype);
			return (-j - 1);
		}
	}
	return (quotesize + 2);
}

void	cpy_text_wquote(t_varchar *cpytext)
{
	char	quotetype;

	quotetype = cpytext->str[cpytext->i];
	cpytext->str2[cpytext->j] = cpytext->str[cpytext->i];
	cpytext->i++;
	cpytext->j++;
	while (cpytext->str[cpytext->i] != quotetype)
	{
		cpytext->str2[cpytext->j] = cpytext->str[cpytext->i];
		cpytext->i++;
		cpytext->j++;
	}
	cpytext->str2[cpytext->j] = cpytext->str[cpytext->i];
	cpytext->i++;
	cpytext->j++;
}

void	cpy_text_noquote(t_varchar *cpytext, t_msvar *env)
{
	char	quotetype;

	quotetype = cpytext->str[cpytext->i];
	cpytext->str2[cpytext->j] = cpytext->str[cpytext->i];
	cpytext->i++;
	while (cpytext->str[cpytext->i] != quotetype)
	{
		if (quotetype == '\"' && cpytext->str[cpytext->i] == '$')
			add_dollar_data(cpytext, env);
		else
		{
			cpytext->str2[cpytext->j] = cpytext->str[cpytext->i];
			cpytext->i++;
			cpytext->j++;
		}
	}
	cpytext->i++;
}

t_varchar	*fillvarchar(char *str, char *str2, int i, int j)
{
	t_varchar	*varchar;

	varchar = malloc(sizeof (t_varchar));
	varchar->str = str;
	varchar->str2 = str2;
	varchar->i = i;
	varchar->j = j;
	return (varchar);
}
