/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:19:16 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/07 17:30:28 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_infile(t_list *cmd, size_t infile_len, t_msvar *env)
{
	t_varchar	*cpyin;

	cmd->infile = malloc(infile_len + 1);
	cpyin = fillvarchar(cmd->cmd_tmp, cmd->infile, 0, 0);
	while (cmd->cmd_tmp[cpyin->i] && cmd->cmd_tmp[cpyin->i] != '<')
		cpyin->i+= cntchar(cmd->cmd_tmp, '<', cpyin->i);
	if (cmd->cmd_tmp[cpyin->i++] == '<')
	{
		if (cmd->cmd_tmp[cpyin->i] == '<')
		{
			cpyin->i++;
			cmd->infileflag = 2;
		}
		else
			cmd->infileflag = 1;
		cpyin->i = no_space(cmd->cmd_tmp, cpyin->i);
		while (cmd->cmd_tmp[cpyin->i] && cmd->cmd_tmp[cpyin->i] != ' ')
		{
			if (cmd->cmd_tmp[cpyin->i] == ('\"') || cmd->cmd_tmp[cpyin->i] == ('\''))
				cpy_text_noquote(cpyin, env);
			cmd->infile[cpyin->j++] = cmd->cmd_tmp[cpyin->i++];
		}
	}
	cmd->infile[cpyin->j] = 0;
	free(cpyin);
}

void	ft_fill_outfile(t_list *cmd, size_t outfile_len, t_msvar *env)
{
	t_varchar	*cpyin;

	cmd->outfile = malloc(outfile_len + 1);
	cpyin = fillvarchar(cmd->cmd_tmp, cmd->outfile, 0, 0);
	while (cmd->cmd_tmp[cpyin->i] && cmd->cmd_tmp[cpyin->i] != '>')
		cpyin->i+= cntchar(cmd->cmd_tmp, '>', cpyin->i);
	if (cmd->cmd_tmp[cpyin->i++] == '>')
	{
		if (cmd->cmd_tmp[cpyin->i] == '>')
		{
			cpyin->i++;
			cmd->outfileflag = 2;
		}
		else
			cmd->outfileflag = 1;
		cpyin->i = no_space(cmd->cmd_tmp, cpyin->i);
		while (cmd->cmd_tmp[cpyin->i] && cmd->cmd_tmp[cpyin->i] != ' ')
		{
			if (cmd->cmd_tmp[cpyin->i] == ('\"') || cmd->cmd_tmp[cpyin->i] == ('\''))
				cpy_text_noquote(cpyin, env);
			cmd->outfile[cpyin->j++] = cmd->cmd_tmp[cpyin->i++];
		}
	}
	cmd->outfile[cpyin->j] = 0;
	free(cpyin);
}

int	no_space(char *src, int i)
{
	while (src[i] == ' ')
		i++;
	return (i);
}

static int	pass_infile(char *src, int i)
{
	if (src[i] != '<')
		printf("error pass_infile\n");
	i++;
	if (src[i] == '<')
		i++;
	while(src[i] == ' ')
		i++;
	if (src[i] == '\''  )
		i += quotesize_incl(src, i, '\'');
	else if (src[i] == '\"')
		i += quotesize_incl(src, i, '\"');
	while(src[i] != ' ' && src[i] != 0)
		i++;
	while(src[i] == ' '&& src[i] != 0)
		i++;
	return (i);
}

static int	pass_outfile(char *src, int i)
{
	if (src[i] != '>')
		printf("error pass_infile\n");
	i++;
	if (src[i] == '>')
		i++;
	while(src[i] == ' ')
		i++;
	if (src[i] == '\''  )
		i += quotesize_incl(src, i, '\'');
	else if (src[i] == '\"')
		i += quotesize_incl(src, i, '\"');
	while(src[i] != ' ' && src[i] != 0)
		i++;
	while(src[i] == ' '&& src[i] != 0)
		i++;
	return (i);
}

void	ft_clean_cmdline(t_list *cmd)
{
	t_varchar	*cmdclean;

	cmdclean = fillvarchar(cmd->cmd_tmp, ft_strdup(cmd->cmd_tmp), 0, 0);
	cmdclean->i = no_space(cmd->cmd_tmp, cmdclean->i);
	while(cmd->cmd_tmp[cmdclean->i] && cmd->cmd_tmp[cmdclean->i])
	{
		if (cmd->cmd_tmp[cmdclean->i] == '\''
			|| cmd->cmd_tmp[cmdclean->i] == '\"')
			cpy_text_wquote(cmdclean);
		if (cmd->cmd_tmp[cmdclean->i] == '<')
			cmdclean->i = pass_infile(cmd->cmd_tmp, cmdclean->i);
		else if (cmd->cmd_tmp[cmdclean->i] == '>')
			cmdclean->i = pass_outfile(cmd->cmd_tmp, cmdclean->i);
		else if (cmd->cmd_tmp[cmdclean->i])
			cmdclean->str2[cmdclean->j++]= cmd->cmd_tmp[cmdclean->i++];
	}
	while(cmdclean->str2[cmdclean->j])
		cmdclean->str2[cmdclean->j++] = 0;
	while(cmdclean->str2[--cmdclean->j] == ' ')
		cmdclean->str2[cmdclean->j] = 0;
	free (cmd->cmd_tmp);
	cmd->cmd_tmp = ft_strdup(cmdclean->str2);
	free (cmdclean->str2);
	free(cmdclean);
}
