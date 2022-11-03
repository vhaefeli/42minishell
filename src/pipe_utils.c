/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/01 14:57:07 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	in_out_fd(t_list *list_cmds, int *fd)
{
	int	infile;
	int	outfile;

	infile = check_file_in(list_cmds, fd[0]);
	outfile = check_file_out(list_cmds, fd[1]);
	if (infile > -1)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	if (outfile > -1)
	{
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
	return (0);
}

static void	fd_init(int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
}

static void	fd_close(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
}

int	pipex(t_list *list_cmds, t_msvar *ms_env)
{
	int	fd[2];
	int	pid;
	int	n_cmd;

	fd_init(fd);
	n_cmd = 0;
	if (!list_cmds->next && checkbuiltin(list_cmds->cmd_with_flags[0]) > 3)
		return (execbuiltin(list_cmds,
				checkbuiltin(list_cmds->cmd_with_flags[0]), ms_env));
	while (list_cmds && ++n_cmd)
	{
		if (ft_fillpath_cmd(list_cmds, ms_env))
			return (1);
		if (list_cmds->next && pipe(fd) == -1 && printf("Pipe error\n"))
			break ;
		pid = fork();
		one_cmd(list_cmds, ms_env, fd, pid);
		list_cmds = list_cmds->next;
		if (list_cmds)
			list_cmds->infile_fd = dup(fd[0]);
		fd_close(fd);
	}
	while (n_cmd--)
		waitpid(pid, NULL, 0);
	return (0);
}

int	ft_pipe(char *cmdline, t_msvar *ms_env)
{
	t_list	*cmd_list;
	int		ret;

	cmd_list = list_cmds(cmdline, ms_env);
	if (cmd_list == NULL)
	{
		printf("error with cmds listing\n");
		return (1);
	}
	ret = pipex(cmd_list, ms_env);
	ms_env->ret = ret;
	del_list(cmd_list);
	free_env(ms_env->env);
	return (0);
}
