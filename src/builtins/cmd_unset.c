/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:36:45 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/02 11:01:59 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_msvar *msvar, t_env *env)
{
	if (msvar->env == env && env->next == NULL)
	{
		ft_memdel(msvar->env->value);
		msvar->env->value = NULL;
		msvar->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(char **a, t_msvar *msvar)
{
	t_env	*env;
	t_env	*tmp;

	env = msvar->env;
	if (!(a[1]))
		return (0);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		if (env->next)
			msvar->env = env->next;
		free_node(msvar, env);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(msvar, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	update_msenv(msvar);
	return (0);
}
