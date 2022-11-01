/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlefebvr <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:33:56 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/10/18 10:34:01 by tlefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (0);
}
