/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:22:54 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/03 14:48:46 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_pwd(char **cmd)
{
	char	*buf;
	if (cmd[1])
	{
		ft_putendl_fd("pwd: too many arguments", 2);
		return(1);
	}
	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
