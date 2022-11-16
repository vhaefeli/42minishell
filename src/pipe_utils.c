/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/16 11:54:31 by vhaefeli         ###   ########.fr       */
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
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
}

int	pipex(t_list *list_cmds, t_msvar *ms_env)
{
	int	fd[2];
	int	n_cmd;

	fd_init(fd);
	n_cmd = 1;
	if (!list_cmds->next
		&& (ms_env->env || (checkbuiltin(list_cmds->cmd_with_flags[0]) == 4))
		&& checkbuiltin(list_cmds->cmd_with_flags[0]) > 3)
		return (execbuiltin(list_cmds,
				checkbuiltin(list_cmds->cmd_with_flags[0]), ms_env));
	update_msenv(ms_env);
	while (list_cmds && ++n_cmd)
	{
		if (ft_fillpath_cmd(list_cmds, ms_env))
			return (1);
		if (list_cmds->next && pipe(fd) == -1 && printf("Pipe error\n"))
			break ;
		list_cmds->cmd_pid = fork();
		one_cmd(list_cmds, ms_env, fd);
		list_cmds = list_cmds->next;
		if (list_cmds)
			list_cmds->infile_fd = dup(fd[0]);
		fd_close(fd);
	}
	return (0);
}

int	ft_pipe(char *cmdline, t_msvar *ms_env)
{
	t_list	*cmd_list;

	cmd_list = list_cmds(cmdline, ms_env);
	if (cmd_list == NULL)
	{
		printf("error with cmds listing\n");
		ms_env->ret = 1;
		return (1);
	}
	if (ms_env->ret == -240)
	{
		del_list(cmd_list);
		return (1);
	}
	if (cmd_list->cmd_with_flags)
	{
		pipex(cmd_list, ms_env);
		wait_all(cmd_list, ms_env);
	}
	del_list(cmd_list);
	if (access(".heredoc", F_OK) == 0)
	{
		unlink(".heredoc");
	}
	return (0);
}
