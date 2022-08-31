/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/31 16:52:42 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcometext(void)
{
	printf("\nW       W   EEEEEE   L       CCCC    OOOO      MM");
	printf("   MM   EEEEEE\n");
	printf("W       W   E        L     CC      OO    OO    M M M M   E\n");
	printf(" W  W  W    EEEE     L     C      O        O   M  M  M   EEEE\n");
	printf("  WW WW     E        L     CC      OO    OO    M     M   E\n");
	printf("  W   W     EEEEEE   LLLLL   CCCC    OOOO      M     M   EEEEEE\n");
	printf("\n");
}

int main (int argc, char **argv, char **envp)
{
	t_msvar *ms_env;
	t_list	*cmdslist;
	char	*cmdline;

	ms_env = ini_ms(envp);
	welcometext();
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
