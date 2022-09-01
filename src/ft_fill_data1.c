/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:19:16 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/09/01 09:29:00 by vhaefeli         ###   ########.fr       */
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

int	ft_clean_space(int i, char *str)
{
	while (str[i] == ' ' && str[i])
			i++;
	return (i);
}

char	switchinout(char first_c);
{
		if (first_c == '<')
		return ('>');
	else
		return ('<');
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
	printf("pre cleaned_cmd:%s-\n len: %lu\n", cmd_tmp, cmdlen);
	first_c = whos_first(cmd_tmp);
	cleaned_cmd = malloc(cmdlen + 1);
	cleaned_cmd[cmdlen] = 0;
	k = ft_cntchar(cmd_tmp, first_c, 0);
	printf("k1:%d\n", k);
	while (i < k && cmd_tmp[i] && cleaned_cmd[j])
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
		i = ft_clean_space(i, cmd_tmp);
		while (cmd_tmp[i] && cmd_tmp[i] != ' ')
			i++;
	}
	first_c = switchinout(first_c);
	k = ft_cntchar(cmd_tmp, first_c, 0);
	printf("k2:%d\n", k);
	i = ft_clean_space(i, cmd_tmp);
	while (i < k && cmd_tmp[i] && cleaned_cmd[j])
	{
		printf("i: %d j:%d\n", i, j);
		cleaned_cmd[j] = cmd_tmp[i];
		i++;
		j++;
	}
	if (cmd_tmp[i] == first_c)
	{
		i++;
		if (cmd_tmp[i] == first_c)
			i++;
		while (cmd_tmp[i] == ' ' && cmd_tmp[i])
			i++;
		while (cmd_tmp[i] && cmd_tmp[i] != ' ' && cmd_tmp[i])
			i++;
	}
	while (cmd_tmp[i] == ' ' && cmd_tmp[i])
		i++;
	while (cmd_tmp[i])
	{
		cleaned_cmd[j] = cmd_tmp[i];
		i++;
		j++;
	}
	printf("i: %d j:%d\n", i, j);
	cleaned_cmd[j] = 0;
	// free (cmd_tmp);
	printf("cleaned_cmd:%s", cleaned_cmd);
	return (cleaned_cmd);
}
