/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:43:24 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/26 16:58:34 by vhaefeli         ###   ########.fr       */
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


int	ft_cmd_error(t_list *list_cmds, int error_type, t_msvar *ms_env)
{
	if (list_cmds)
		del_list(list_cmds);
	ms_env->prev_ret = ms_env->ret;
	ms_env->ret = error_type;
	printf("\n prev_ret = %i", ms_env->prev_ret); //le problem est que la commande change de maniere dznamique sa doit prendre la version d'avant
	return (ms_env->ret);
}

int	ft_exit_minishell(t_msvar *ms_env)
{
	// int	i;

	free(ms_env);
	// faire une fonction qui free le ms_env et tout ce qui peut trainer.
	// i = 0;
	// 	if (path)
	// {
	// 	while (path[i])
	// 	{
	// 		free(path[i]);
	// 		i++;
	// 	}
	// 	free(path);
	// }
	printf("Bye Bye! See you soon :oD");
	return (0);
}