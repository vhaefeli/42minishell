/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:07:34 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/10 13:46:02 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fonct_ret(t_varchar *env_data, t_msvar *env)
{
	env_data->str = malloc(2);
	env_data->str[0] = '?';
	env_data->i = 1;
	env_data->str2 = ft_itoa(env->ret);
	env_data->j = 1;
}

t_varchar	*dollar_data(char *str, int i, t_msvar *env)
{
	char		*env_datatmp;
	t_varchar	*env_data;

	env_datatmp = malloc(1000);
	env_data = malloc(sizeof (t_varchar));
	env_data->j = 0;
	i++;
	if (str[i] == '?')
		fonct_ret(env_data, env);
	else
	{
		while ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= 'a' && str[i] <= 'z') || (str[i] == '_'))
		{
			env_datatmp[env_data->j++] = str[i++];
		}
		env_datatmp[env_data->j] = 0;
		env_data->str = ft_strdup(env_datatmp);
		env_data->i = ft_strlen(env_data->str);
		env_data->str2 = get_env_value(env_datatmp, env->env);
		env_data->j = ft_strlen(env_data->str2);
	}
	free(env_datatmp);
	return (env_data);
}

void	add_dollar_data(t_varchar *src, t_msvar *env)
{
	t_varchar	*datatmp;
	int			i;

	i = 0;
	datatmp = dollar_data(src->str, src->i, env);
	if (datatmp->i + 1 < datatmp->j)
	{
		src->str2 = ft_realloc(src->str2, ft_strlen(src->str) + datatmp->j);
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

char	*ft_realloc(char *src, int new)
{
	char	*newstr;
	int		i;

	i = 0;
	newstr = ft_calloc(new + 1, sizeof(char));
	while (src[i] && i < new)
	{
		newstr[i] = src[i];
		i++;
	}
	free(src);
	return (newstr);
}
