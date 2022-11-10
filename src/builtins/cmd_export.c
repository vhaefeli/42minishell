/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:12:17 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/09 11:29:09 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", 2);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", 2);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(2, &arg[i], 1);
		i++;
	}
	write(2, "\n", 1);
	return (1);
}

int	ft_export(char **args, t_msvar *envp)
{
	int		new_env;
	int		error_ret;

	new_env = 0;
	if (!args[1])
	{
		print_sorted_env(envp->env);
		return (0);
	}
	else
	{
		error_ret = is_valid_env(args[1]);
		if (args[1][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
			return (print_error(error_ret, args[1]));
		if (error_ret == 2)
			new_env = 1;
		else
			new_env = is_in_env(envp->env, args[1]);
		if (new_env == 0 && error_ret == 1)
			env_add(args[1], envp->env);
	}
	return (0);
}
