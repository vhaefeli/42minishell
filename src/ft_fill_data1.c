/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:19:16 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/10 20:19:54 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_infile(t_list *cmd, size_t infile_len)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	cmd->infile = malloc(infile_len + 1);
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '<')
		i+= ft_cntchar(cmd->cmd_tmp, '<', i);
	if (cmd->cmd_tmp[i++] == '<')
	{
		if (cmd->cmd_tmp[i] == '<')
		{
			i++;
			cmd->infileflag = 2;
		}
		else
			cmd->infileflag = 1;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] == ' ')
			i++;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != ' ')
			cmd->infile[j++] = cmd->cmd_tmp[i++];
	}
}

void	ft_fill_outfile(t_list *cmd, size_t outfile_len)
{
	int	i;
	int j;
	
	i = 0;
	j = 0;
	cmd->outfile = malloc(outfile_len + 1);
	while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != '>')
		i+= ft_cntchar(cmd->cmd_tmp, '>', i);
	if (cmd->cmd_tmp[i++] == '>')
	{
		if (cmd->cmd_tmp[i] == '>')
		{
			i++;
			cmd->outfileflag = 2;

		}
		else
			cmd->outfileflag = 1;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] == ' ')
			i++;
		while (cmd->cmd_tmp[i] && cmd->cmd_tmp[i] != ' ')
		{
			cmd->outfile[j] = cmd->cmd_tmp[i];
			i++;
			j++;
		}
	}
}

static char	whos_first(char *cmdline)
{
	int	in;
	int	out;

	in = ft_cntchar(cmdline, '<', 0);
	out = ft_cntchar(cmdline, '>', 0);
	if (in < out)
		return ('<');
	else
		return ('>');
}

char	*ft_clean_cmdline(char *cmd_tmp, size_t cmdlen)
{
	int		i;
	int		j;
	int		k;
	char	first_c;
	char	*cleaned_cmd;
	
	i = 0;
	j = 0;
	first_c = whos_first(cmd_tmp);
	cleaned_cmd = malloc(cmdlen + 1);
	k = ft_cntchar(cmd_tmp, first_c, 0);
	while (i < k && cmd_tmp[i])
	{
		cleaned_cmd[j] = cmd_tmp[i];
		i++;
		j++;
	}
	if (cmd_tmp[i] == first_c)
	{
		i++;
		if (cmd_tmp[i] == first_c)
			i++;
		while (cmd_tmp[i] == ' ')
			i++;
		while (cmd_tmp[i] && cmd_tmp[i] != ' ')
			i++;
	}
	if (first_c == '<')
		first_c = '>';
	else
		first_c = '<';
	k = ft_cntchar(cmd_tmp, first_c, 0);
	while (i < k && cmd_tmp[i])
	{
		cleaned_cmd[j] = cmd_tmp[i];
		i++;
		j++;
	}
	if (cmd_tmp[i] == first_c)
	{
		i++;
		if (cmd_tmp[i] == first_c)
			i++;
		while (cmd_tmp[i] == ' ')
			i++;
		while (cmd_tmp[i] && cmd_tmp[i] != ' ')
		i++;
	}
	while (cmd_tmp[i])
	{
		cleaned_cmd[j] = cmd_tmp[i];
		i++;
		j++;
	}
	cleaned_cmd[j] = 0;
	// free (cmd_tmp);
	return (cleaned_cmd);
}