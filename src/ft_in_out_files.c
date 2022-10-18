/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:09:17 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/18 10:06:11 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_infile(char *cmdline, size_t i)
{
	size_t	j;

	j = 0;
	// while (cmdline[i] && cmdline[i] != '<')
	// 	i+= cntlchar(cmdline, '<', i);
	// // printf("i= %zu\n",i);
	// if (cmdline[i] == '<')
	// {
		i++;
		// printf("checkinfile1 c: %c\n", cmdline[i]);
		if (cmdline[i] == '<')
			i++;
		i = no_space(cmdline, i);
		// printf("i= %zu\n",i);
		j = cntchar_noquote(cmdline, ' ', i);
	// }
	// printf("infile len :%zu\n", j);
	return (j);
}

size_t	check_outfile(char *cmdline, size_t i)
{
	size_t	j;

	j = 0;
	while (cmdline[i] && cmdline[i] != '>')
		i+= cntchar(cmdline, '>', i);
	if (cmdline[i] == '>')
	{
		i++;
		if (cmdline[i] == '>')
			i++;
		i = no_space(cmdline, i);
		j = cntchar_noquote(cmdline, ' ', i);
	}
	return (j);
}

void	ft_check_in_out(t_list *cmd, t_msvar *ms_env)
{
	int	i;

	i = 0;
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '<')
	{
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '<')
			i+= cntlchar(cmd->cmd_tmp, '<', i);
		if (cmd->cmd_tmp[i] == '<')
		{
			i = ft_fill_infile(cmd, ms_env, i);
			if (infile_ok(cmd) != 0)
				break;
		}
	}
	i = 0;
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '<')
	{
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '<')
			i+= cntlchar(cmd->cmd_tmp, '<', i);
		if (cmd->cmd_tmp[i] == '<')
		{
			i = ft_fill_infile(cmd, ms_env, i);
			if (infile_ok(cmd) != 0)
				break;
		}
	}
}

void	ft_in_out_files(t_list *cmds, t_msvar *ms_env)
{
	while (cmds)
	{
		ft_check_in_out(cmds, ms_env);
		cmds = (cmds)->next;
	}
}

