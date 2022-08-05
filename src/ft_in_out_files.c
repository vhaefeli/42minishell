/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:09:17 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/05 23:43:45 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	check_infile(char *cmdline)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmdline[i] && cmdline[i] != '<')
		i+= ft_cntchar(cmdline, '<', i);
	if (cmdline[i++] == '<')
	{
		j++;
		if (cmdline[i] == '<')
		{
			i++;
			j++;
		}
		while (cmdline[i++] == ' ')
			j++;
		while (cmdline[i++] != ' ')
			j++;
	}
	return (j);
}

size_t	check_outfile(char *cmdline)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmdline[i] != '>')
		i+= ft_cntchar(cmdline, '>', i);
	if (cmdline[i++] == '>')
	{
		j++;
		if (cmdline[i] == '>')
		{
			i++;
			j++;
		}
		while (cmdline[i++] == ' ')
			j++;
		while (cmdline[i++] != ' ')
			j++;
	}
	return (j);
}

void	ft_check_in_out(t_list *cmd)
{
	size_t	cmdline_len;
	size_t	infile_len;
	size_t	outfile_len;
	size_t	cmd_wflag_len;

	printf("cmd_temp avant traitement: %s\n", cmd->cmd_tmp);
	cmdline_len = ft_strlen(cmd->cmd_tmp);
	infile_len = check_infile(cmd->cmd_tmp);
	outfile_len = check_outfile(cmd->cmd_tmp);
	cmd_wflag_len = cmdline_len - infile_len - outfile_len;
	if (infile_len > 0)
		ft_fill_infile(cmd, infile_len);
	printf("infile: %s flag %i\n", cmd->infile, cmd->infileflag);
	if (outfile_len > 0)
		ft_fill_outfile(cmd, outfile_len);
	printf("outfile: %s flag %i\n", cmd->outfile, cmd->outfileflag);
	if (cmd_wflag_len < cmdline_len)
		cmd->cmd_tmp = ft_clean_cmdline(cmd->cmd_tmp, cmd_wflag_len);
	printf("cmd_temp apres traitement: %s\n", cmd->cmd_tmp);
}

void	ft_in_out_files(t_list *cmds)
{
	while (cmds)
	{
		ft_check_in_out(cmds);
		cmds = (cmds)->next;
	}
}