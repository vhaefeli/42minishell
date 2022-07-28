/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:49:31 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/28 22:37:59 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_pipe_split(char *cmdline, t_list *cmd, int i)
{
	int	fullcmdsize;
	int j;

	j = 0;
	if (! cmdline)
		return (-1);
	fullcmdsize = ft_cntchar(cmdline, '\|', i);
	cmd->cmd_tmp = malloc(fullcmdsize + 1);
	if (!cmd->cmd_tmp)
		return (-1);
	while (i < fullcmdsize)
	{
		cmd->cmd_tmp[j] = cmdline[i];
		i++;
		j++;
	}
	cmd->cmd_tmp[j] = 0;
	if (cmdline[i] = 0)
		return (i);
	return (i + 1);
}
