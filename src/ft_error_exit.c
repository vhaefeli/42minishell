/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:43:24 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/05 23:34:24 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// attention pas de exit qui fermerait minishell

// int	ft_errortype
// 0 pas d erreur
// 1 erreur generique
// 2 erreur de commande
// 3 erreur infile outfile
// 4 erreur cmd builtin


int	ft_cmd_error(t_list *list_cmds, int error_type)
{
	if (list_cmds)
		del_list(list_cmds);
	return (error_type);
}

int	ft_exit_minishell(char **path)
{
	int	i;

	i = 0;
		if (path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	printf("Bye Bye! See you soon :oD");
	return (0);
}