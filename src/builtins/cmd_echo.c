/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:34:52 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/01 11:59:04 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_echo(char **args)
{
	int	nflag;
	int	i;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	nflag = ft_strcmp(args[1], "-n");
	if (nflag)
		i = 1;
	else
		i = 2;
	while (args[i])
	{
		printf ("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (nflag)
		printf("\n");
	return (0);
}
