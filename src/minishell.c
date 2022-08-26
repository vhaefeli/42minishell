/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/26 18:05:42 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main (int argc, char **argv, char **envp)
{
	t_msvar *ms_env;
	t_list	*cmdslist;
	char	*cmdline;

	ms_env = ini_ms(envp);
	while (1)
	{
		cmdline = readline("minishell> ");
		if (!cmdline)
			break ;
		ft_pipe( cmdline, ms_env);
		free(cmdline);
	}
    return (0);
}