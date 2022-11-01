/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:07:34 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/01 11:48:09 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fonct_ret(t_varchar *env_data, t_msvar *env)
{
	env_data->str = malloc(2);
	env_data->str[0] = '?';
	env_data->i = 1;
	env_data->str2 = ft_itoa(env->prev_ret);
	env_data->j = 1;
	env->ret = 1;
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
