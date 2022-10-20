/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_out_files3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:57:55 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/20 15:06:53 by vhaefeli         ###   ########.fr       */
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

int	pass_outfile(char *src, int i)
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

int	check_file_in(t_list *cmd, int *fd)
{
	if (cmd->infile != NULL)
	{
		if (cmd->infileflag == 1)
		{
			return (open(cmd->infile, O_RDONLY));
		}
		if (cmd->infileflag == 2)
		{
			return (open(".heredoc", O_RDONLY));
		}
	}
	if (cmd->previous)
	{
		return (fd[0]);
	}
	return (0);
}

void	check_file_out(t_list *cmd, int *fd, t_msvar *ms_env)
{
	int file;

	if (cmd->outfile != NULL)
	{
		if (cmd->outfileflag == 1)
		{
			file = open(cmd->outfile, O_WRONLY | O_TRUNC);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
		if (cmd->outfileflag == 2)
		{
			file = open(cmd->outfile, O_WRONLY | O_APPEND);
			dup2(file, STDOUT_FILENO);
			close(file);
		}
	}
	else if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(ms_env->stdout_fd, STDOUT_FILENO);
}
