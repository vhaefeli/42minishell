/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:43:24 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/01 11:53:39 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_error(t_list *list_cmds, int error_type, t_msvar *ms_env)
{
	ms_env->ret = error_type;
	return (ms_env->prev_ret);
}

int	ft_exit_minishell(t_msvar *ms_env)
{
	free(ms_env);
	printf("Bye Bye! See you soon :oD");
	return (0);
}
