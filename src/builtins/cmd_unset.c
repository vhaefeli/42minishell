/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:36:45 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/15 16:07:02 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	ft_unset_suite(t_env *env, t_msvar *msvar)
{
	if (env->next)
		msvar->env = env->next;
	free_node(msvar, env);
}

static int	ft_value_cmp(char *a, char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && b[i] != '=')
	{
		if (a[i] == b[i])
		{
			i++;
		}
		else
			break ;
	}
	if (a[i] == 0 && b[i] == '=')
	{
		return (0);
	}
	else
		return (1);
}

int	ft_unset(char **a, t_msvar *msvar)
{
	t_env	*env;
	t_env	*tmp;

	env = msvar->env;
	if (!(a[1]))
		return (0);
	if (ft_value_cmp(a[1], env->value) == 0)
	{
		ft_unset_suite(env, msvar);
		return (0);
	}
	while (env && env->next)
	{
		if (ft_value_cmp(a[1], env->next->value) == 0)
		{
			tmp = env->next->next;
			free_node(msvar, env->next);
			env->next = tmp;
			return (0);
		}
		env = env->next;
	}
	return (0);
}
