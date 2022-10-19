/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:09:17 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/18 18:48:28 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	infile_ok(t_list *cmd)
{
	// printf("infile %s\n", cmd->infile);
	if (cmd->infile != NULL)
	{
		if (cmd->infileflag == 1)
		{
			if (cmd->infile[0] == 0)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (-1);
			}
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
			cmd->infileflag = ft_heredoc(cmd);
	}
	return (0);
}

int	outfile_ok(t_list *cmd)
{
	int	file;

	// printf("outfile %s\n", cmd->outfile);
	if (cmd->outfile != NULL)
	{
		if (access(cmd->outfile, F_OK) != 0)
		{
			file = open(cmd->outfile, O_CREAT, 0644);
			close(file);
		}
		if (access(cmd->outfile, W_OK) != 0)
		{
			printf("(Error) %s : %s \n", strerror(errno), cmd->outfile);
			return (-1);
		}
	}
	return (0);
}

int	fill_inout(t_list *cmd, t_msvar *ms_env, int i, char c)
{
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != c)
		i+= cntchar(cmd->cmd_tmp, c, i);
	if (cmd->cmd_tmp[i] == '<')
	{
		if (cmd->infile)
			del_el(cmd->infile);
		i = ft_fill_infile(cmd, ms_env, i);
		if (infile_ok(cmd) != 0)
			return (-1);
	}
	else if (cmd->cmd_tmp[i] == '>')
	{
		i = ft_fill_outfile(cmd, ms_env, i);
		if (outfile_ok(cmd) != 0)
			return (-1);
	}
	return (i);
}

int	ft_check_in_out(t_list *cmd, t_msvar *ms_env)
{
	int	i;

	i = 0;
	while (cmd->cmd_tmp[i])
	{
		i = fill_inout(cmd, ms_env, i, '<');
		if (i == -1)
			return (1);
	}
	i = 0;
	while (cmd->cmd_tmp[i])
	{
		i = fill_inout(cmd, ms_env, i, '>');
		if (i == -1)
			return (1);
	}
	return (0);
}

int	ft_in_out_files(t_list *cmds, t_msvar *ms_env)
{
	int	check_error;

	while (cmds)
	{
		check_error = ft_check_in_out(cmds, ms_env);
		if (check_error)
			return (1);
		cmds = (cmds)->next;
	}
	return (0);
}

