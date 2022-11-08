/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 21:19:16 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/04 16:05:58 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_space(char *src, int i)
{
	while (src[i] == ' ')
		i++;
	return (i);
}

void	ft_clean_cmdline(t_list *cmd)
{
	t_varchar	*cmdclean;

	cmdclean = fillvarchar(cmd->cmd_tmp, ft_strdup(cmd->cmd_tmp), 0, 0);
	cmdclean->i = no_space(cmd->cmd_tmp, cmdclean->i);
	while (cmd->cmd_tmp[cmdclean->i])
	{
		if (cmd->cmd_tmp[cmdclean->i] == '\''
			|| cmd->cmd_tmp[cmdclean->i] == '\"')
			cpy_text_wquote(cmdclean);
		if (cmd->cmd_tmp[cmdclean->i] == '<')
			cmdclean->i = pass_infile(cmd->cmd_tmp, cmdclean->i);
		else if (cmd->cmd_tmp[cmdclean->i] == '>')
			cmdclean->i = pass_outfile(cmd->cmd_tmp, cmdclean->i);
		else if (cmd->cmd_tmp[cmdclean->i])
			cmdclean->str2[cmdclean->j++] = cmd->cmd_tmp[cmdclean->i++];
	}
	cmdclean->str2[cmdclean->j] = 0;
	while (cmdclean->j > 0 && cmdclean->str2[--cmdclean->j] == ' ')
		cmdclean->str2[cmdclean->j] = 0;
	free (cmd->cmd_tmp);
	cmd->cmd_tmp = ft_strdup(cmdclean->str2);
	free (cmdclean->str2);
	free(cmdclean);
}
