/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:42:13 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/04 22:41:48 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_text_between_space(t_varchar *src, t_msvar *env)
{
	src->i = no_space(src->str, src->i);
	while (src->str[src->i] && src->str[src->i] != ' ')
	{
		if (src->str[src->i] == '$')
		{
			add_dollar_data(src, env);
		}
		if (src->str[src->i] == ('\"') || src->str[src->i] == ('\''))
			cpy_text_noquote(src, env);
		src->str2[src->j++] = src->str[src->i++];
	}
}

void	add_dollar_data(t_varchar *src, t_msvar *env)
{
	t_varchar	*datatmp;
	int			i;

	i = 0;
	datatmp = dollar_data(src->str, src->i, env);

	if (datatmp->i + 1 < datatmp->j)
	{
		src->str2 = ft_realloc(src->str2, datatmp->j - (datatmp->i + 1));
	}
	src->i += (datatmp->i + 1);
	while (datatmp->str2 && datatmp->str2[i])
	{
		src->str2[src->j++] = datatmp->str2[i++];
	}
	free(datatmp->str);
	free(datatmp->str2);
	free(datatmp);
}

char	*ft_realloc(char *src, int diff)
{
	char	*newstr;
	int		len;

	len = ft_strlen(src) + diff;
	newstr = ft_calloc(len + 1, 1);
	free(src);
	return (newstr);
}
