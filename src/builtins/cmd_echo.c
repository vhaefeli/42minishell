/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlefebvr <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:34:52 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/10/18 10:34:54 by tlefebvr         ###   ########.fr       */
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
			printf (" ");
	}
	if (nflag)
		printf ("\n");
	return (0);
}
