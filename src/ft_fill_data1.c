/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:19:16 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/09/01 19:06:05 by vhaefeli         ###   ########.fr       */
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
	cmd->infile[j] = 0;
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
	cmd->outfile[j] = 0;
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

char	switchinout(char first_c)
{
		if (first_c == '<')
		return ('>');
	else
		return ('<');
}

void	clean_file(int k, t_varchar *cmd, char first_c)
{
	while (cmd->str[cmd->i] == ' ' && cmd->str[cmd->i])
			cmd->i++;
	while (cmd->i < k && cmd->str[cmd->i] && cmd->str2[cmd->j])
	{
		cmd->str2[cmd->j] = cmd->str[cmd->i];
		cmd->i++;
		cmd->j++;
	}
	if (cmd->str[cmd->i] == first_c)
	{
		cmd->i++;
		if (cmd->str[cmd->i] == first_c)
			cmd->i++;
		while (cmd->str[cmd->i] == ' ' && cmd->str[cmd->i])
			cmd->i++;
		while (cmd->str[cmd->i] && cmd->str[cmd->i] != ' ')
			cmd->i++;
	}
}

char	*ft_clean_cmdline(char *cmd_tmp, size_t cmdlen)
{
	t_varchar	cmd;
	int		k;
	char	first_c;

	cmd.i = 0;
	cmd.j = 0;
	cmd.str = cmd_tmp;
	cmd.str2 = malloc(cmdlen + 1);
	cmd.str2[cmdlen] = 0;
	first_c = whos_first(cmd_tmp);
	k = ft_cntchar(cmd_tmp, first_c, 0);
	clean_file(k, &cmd, first_c);
	first_c = switchinout(first_c);
	k = ft_cntchar(cmd_tmp, first_c, 0);
	clean_file(k, &cmd, first_c);
	k = ft_strlen(cmd_tmp);
	clean_file(k, &cmd, first_c);
	return (cmd.str2);
}
