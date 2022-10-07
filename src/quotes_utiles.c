/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:49:48 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/07 17:28:00 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotesize(char *s, int i, char quotetype)
{
	int	quotesize;
	int	j;

	quotesize = 0;
	j = i;
	i++;
	// printf("s[i]: %c\n", s[i]);
	while(s[i] != quotetype && s[i] != '\0')
	{
		i++;
		quotesize++;
		if (s[i] == '\0')
		{
			printf("error : you can have only an even ");
			printf("number of %c quotes\n", quotetype);
			return (- j - 1);
		}
	}
	// printf("quotesize: %d\n", quotesize);
	return (quotesize);
}

int	quotesize_incl(char *s, int i, char quotetype)
{
	int	quotesize;
	int	j;

	quotesize = 0;
	j = i;
	i++;
	while(s[i] != quotetype && s[i] != '\0')
	{
		i++;
		quotesize++;
		if (s[i] == '\0')
		{
			printf("error : you can have only an even ");
			printf("number of %c quotes\n", quotetype);
			return (- j - 1);
		}
	}
	// printf("quotesize_incl: %d\n", quotesize +2);
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
