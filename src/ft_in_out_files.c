/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:09:17 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/12 12:07:13 by vhaefeli         ###   ########.fr       */
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
		i+= cntchar(cmdline, '<', i);
	// printf("i= %zu\n",i);
	if (cmdline[i] == '<')
	{
		i++;
		// printf("checkinfile1 c: %c\n", cmdline[i]);
		if (cmdline[i] == '<')
			i++;
		i = no_space(cmdline, i);
		// printf("i= %zu\n",i);
		j = cntchar_noquote(cmdline, ' ', i);
	}
	// printf("infile len :%zu\n", j);
	return (j);
}

size_t	check_outfile(char *cmdline)
{
	size_t	i;
	size_t	j;

	i = 0;
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
	size_t	cmdline_len;
	size_t	infile_len;
	size_t	outfile_len;

	cmdline_len = ft_strlen(cmd->cmd_tmp);
	// printf("ft_check_in_out cmdline_len %zu\n", cmdline_len);
	infile_len = check_infile(cmd->cmd_tmp);
	// printf("ft_check_in_out infile_len %zu\n", infile_len);
	outfile_len = check_outfile(cmd->cmd_tmp);
	// printf("ft_check_in_out outfile_len %zu\n", outfile_len);
	if (infile_len > 0)
		ft_fill_infile(cmd, infile_len, ms_env);
	if (outfile_len > 0)
		ft_fill_outfile(cmd, outfile_len, ms_env);
	// printf("ft_check_in_out infile outfile -%s-%s-\n", cmd->infile, cmd->outfile);
}

void	ft_in_out_files(t_list *cmds, t_msvar *ms_env)
{
	while (cmds)
	{
		ft_check_in_out(cmds, ms_env);
		cmds = (cmds)->next;
	}
}
