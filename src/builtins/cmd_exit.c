/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:37:16 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/15 16:06:06 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_exit(t_msvar *msvar, char **cmd)
{
	if (cmd[1] && cmd[2])
	{
		msvar->ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (msvar->ret);
	}
	msvar->exit = 1;
	if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		msvar->ret = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (cmd[1])
		msvar->ret = ft_atoi(cmd[1]);
	else
		msvar->ret = 0;
	return (msvar->ret);
}
