/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:57:55 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/10 15:16:15 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pass_infile(char *src, int i)
{
	if (src[i] != '<')
		printf("error pass_infile\n");
	i++;
	if (src[i] == '<')
		i++;
	while (src[i] == ' ')
		i++;
	if (src[i] == '\'')
		i += quotesize_incl(src, i, '\'');
	else if (src[i] == '\"')
		i += quotesize_incl(src, i, '\"');
	while (src[i] != ' ' && src[i] != 0)
		i++;
	while (src[i] == ' ' && src[i] != 0)
		i++;
	return (i);
}

int	pass_outfile(char *src, int i)
{
	if (src[i] != '>')
		printf("error pass_infile\n");
	i++;
	if (src[i] == '>')
		i++;
	while (src[i] == ' ')
		i++;
	if (src[i] == '\'')
		i += quotesize_incl(src, i, '\'');
	else if (src[i] == '\"')
		i += quotesize_incl(src, i, '\"');
	while (src[i] != ' ' && src[i] != 0)
		i++;
	while (src[i] == ' ' && src[i] != 0)
		i++;
	return (i);
}

int	check_file_in(t_list *cmd, int fd_in)
{
	int	file;

	if (cmd->infile != NULL)
	{
		if (cmd->infileflag == 1)
		{
			file = open(cmd->infile, O_RDONLY);
			return (file);
		}
		else
		{
			file = open(".heredoc", O_RDONLY);
			return (file);
		}
	}
	if (cmd->infile_fd > -1)
		return (cmd->infile_fd);
	else
		return (fd_in);
}

int	check_file_out(t_list *cmd, int fd_out)
{
	int	file;

	if (cmd->outfile != NULL)
	{
		if (cmd->outfileflag == 1)
		{
			file = open(cmd->outfile, O_WRONLY | O_TRUNC);
			return (file);
		}
		else
		{
			file = open(cmd->outfile, O_WRONLY | O_APPEND);
			return (file);
		}
	}
	else
		return (fd_out);
}
