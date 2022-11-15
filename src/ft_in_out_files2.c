/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:35:23 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/15 11:54:05 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	infile_size(char *cmdline, int i)
{
	size_t	j;

	j = 0;
	i++;
	if (cmdline[i] == '<')
		i++;
	i = no_space(cmdline, i);
	j = cntchar_noquote(cmdline, ' ', i);
	return (j);
}

size_t	outfile_size(char *cmdline, int i)
{
	size_t	j;

	j = 0;
	i++;
	if (cmdline[i] == '>')
		i++;
	i = no_space(cmdline, i);
	j = cntchar_noquote(cmdline, ' ', i);
	return (j);
}

int	inoutfileflag_ini(t_list *cmd, int i, char c)
{
	if (c == '<')
	{
		if (cmd->cmd_tmp[i] == '<')
		{
			i++;
			cmd->infileflag = 2;
		}
		else
		cmd->infileflag = 1;
		return (i);
	}
	if (c == '>')
	{
		if (cmd->cmd_tmp[i] == '>')
		{
			i++;
			cmd->outfileflag = 2;
		}
		else
		cmd->outfileflag = 1;
		return (i);
	}
	return (-1);
}

int	ft_fill_infile(t_list *cmd, t_msvar *env, int i)
{
	t_varchar	*ci;
	size_t		infile_len;

	infile_len = infile_size(cmd->cmd_tmp, i);
	del_el(cmd->infile);
	cmd->infile = malloc(infile_len + 1);
	ci = fillvarchar(cmd->cmd_tmp, cmd->infile, i, 0);
	while (cmd->cmd_tmp[ci->i] && cmd->cmd_tmp[ci->i] != '<')
		ci->i += cntchar(cmd->cmd_tmp, '<', ci->i);
	if (cmd->cmd_tmp[ci->i] && cmd->cmd_tmp[ci->i++] == '<')
	{
		ci->i = inoutfileflag_ini(cmd, ci->i, '<');
		ci->i = no_space(cmd->cmd_tmp, ci->i);
		while (cmd->cmd_tmp[ci->i] && cmd->cmd_tmp[ci->i] != ' ')
		{
			if (cmd->cmd_tmp[ci->i] == ('\"') || cmd->cmd_tmp[ci->i] == ('\''))
				cpy_text_noquote(ci, env);
			cmd->infile[ci->j++] = cmd->cmd_tmp[ci->i++];
		}
	}
	cmd->infile[ci->j] = 0;
	free(ci);
	if (cmd->infileflag > 1)
		return (i + 2);
	return (i + 1);
}

int	ft_fill_outfile(t_list *cmd, t_msvar *env, int i)
{
	t_varchar	*co;
	size_t		outfile_len;

	outfile_len = outfile_size(cmd->cmd_tmp, i);
	del_el(cmd->outfile);
	cmd->outfile = malloc(outfile_len + 1);
	co = fillvarchar(cmd->cmd_tmp, cmd->infile, i, 0);
	while (cmd->cmd_tmp[co->i] && cmd->cmd_tmp[co->i] != '>')
		co->i += cntchar(cmd->cmd_tmp, '>', co->i);
	if (cmd->cmd_tmp[co->i] && cmd->cmd_tmp[co->i++] == '>')
	{
		co->i = inoutfileflag_ini(cmd, co->i, '>');
		co->i = no_space(cmd->cmd_tmp, co->i);
		while (cmd->cmd_tmp[co->i] && cmd->cmd_tmp[co->i] != ' ')
		{
			if (cmd->cmd_tmp[co->i] == ('\"') || cmd->cmd_tmp[co->i] == ('\''))
				cpy_text_noquote(co, env);
			cmd->outfile[co->j++] = cmd->cmd_tmp[co->i++];
		}
	}
	cmd->outfile[co->j] = 0;
	free(co);
	if (cmd->outfileflag > 1)
		return (i + 2);
	return (i + 1);
}
