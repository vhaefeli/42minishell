/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_children_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/06/29 21:51:51 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	check_infile(char *cmd_infile, int fd[])
{
	if (cmd_infile != NULL)
	{
		return (open(cmd_infile, O_RDONLY));
	}
	else
		return (fd[0]);
}

static int	check_outfile(char *cmd_outfile, int fd[])
{
	if (cmd_outfile != NULL)
	{
		return (open(cmd_outfile, O_WRONLY | O_TRUNC));
	}
	else
		return (fd[1]);
}

void	child_process(t_list *list_cmds, int fd[], char **envp)
{
	int		infile;
	int		outfile;

	infile = check_infile(list_cmds->infile, fd);
	outfile = check_outfile(list_cmds->outfile, fd);
	if (infile < 0 || outfile < 0)
	{
		close(fd[1]);
		close(fd[0]);
		perror("Fork");
		exit(EXIT_FAILURE);
	}
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	if (fd[0] > -1)
		close(fd[0]);
	if (fd[1] > -1)
		close(fd[1]);
	execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, envp);
}
