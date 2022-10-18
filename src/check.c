/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 22:29:19 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/17 23:25:48 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_ok(t_list *cmd)
{
	printf("infile %s\n", cmd->infile);
	if (cmd->infile != NULL)
	{
		if (cmd->infileflag == 1)
		{
			if (access(cmd->infile, F_OK) != 0)
			{
				printf("(Error) %s : %s \n", strerror(errno), cmd->infile);
				return (-1);
			}
			if (access(cmd->infile, R_OK) != 0)
			{
				printf("(Error) %s : %s \n", strerror(errno), cmd->infile);
				return (-1);
			}
		}
		if (cmd->infileflag > 1)
			cmd->infileflag = ft_heredoc(cmd->infile);
	}
	return (0);
}