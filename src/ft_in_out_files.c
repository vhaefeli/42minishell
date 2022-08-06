/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:09:17 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/06 17:44:14 by vhaefeli         ###   ########.fr       */
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
		while (cmdline[i] && cmdline[i++] == ' ')
			j++;
		while (cmdline[i] && cmdline[i++] != ' ')
			j++;
	}
	printf("check infile j:%zu\n", j);
	return (j);
}

size_t	check_outfile(char *cmdline)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (cmdline[i] && cmdline[i] != '>')
		i+= ft_cntchar(cmdline, '>', i);
	if (cmdline[i++] == '>')
	{
		j++;
		if (cmdline[i] == '>')
		{
			i++;
			j++;
		}
		while (cmdline[i] && cmdline[i++] == ' ')
			j++;
		while (cmdline[i] && cmdline[i++] != ' ')
			j++;
	}
	printf("check outfile j:%zu\n", j);
	return (j);
}

static size_t	ft_cleaned_cmdline_len(t_list *cmd)
{
	size_t	cmdlen;
	
	cmdlen = ft_strlen(cmd->cmd_tmp);
	if (cmd->infileflag == 1)
		cmdlen-= (ft_strlen(cmd->infile) + 2);
	if (cmd->infileflag == 2)
		cmdlen-= (ft_strlen(cmd->infile) + 3);
	if (cmd->outfileflag == 1)
		cmdlen-= (ft_strlen(cmd->outfile) + 2);
	if (cmd->outfileflag == 2)
		cmdlen-= (ft_strlen(cmd->outfile) + 3);
	return (cmdlen);
}

void	ft_check_in_out(t_list *cmd)
{
	size_t	cmdline_len;
	size_t	infile_len;
	size_t	outfile_len;
	size_t	cmd_wflag_len;

	printf("cmd_temp avant traitement:-%s-\n", cmd->cmd_tmp);
	cmdline_len = ft_strlen(cmd->cmd_tmp);
	printf("cmdlinelen: %zu\n", cmdline_len);
	printf("ft_check_in_out 1\n");
	infile_len = check_infile(cmd->cmd_tmp);
	printf("infilelen: %zu\n", infile_len);
	printf("ft_check_in_out 2\n");
	outfile_len = check_outfile(cmd->cmd_tmp);
	printf("outfilelen: %zu\n", outfile_len);
	printf("ft_check_in_out 3\n");
	if (infile_len > 0)
		ft_fill_infile(cmd, infile_len);
	printf("\ninfile: -%s- flag %i\n", cmd->infile, cmd->infileflag);
	if (outfile_len > 0)
		ft_fill_outfile(cmd, outfile_len);
	printf("\noutfile: -%s- flag %i\n", cmd->outfile, cmd->outfileflag);
	cmd_wflag_len = ft_cleaned_cmdline_len(cmd);
	printf("cmdlen: %zu\n", cmd_wflag_len);
	if (cmd_wflag_len < cmdline_len)
		cmd->cmd_tmp = ft_clean_cmdline(cmd->cmd_tmp, cmd_wflag_len);
	printf("\ncmd_temp apres traitement:-%s-\n\n", cmd->cmd_tmp);
}

void	ft_in_out_files(t_list *cmds)
{
	while (cmds)
	{
		ft_check_in_out(cmds);
		cmds = (cmds)->next;
	}
}