/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/31 17:06:17 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void checklistcmd(t_list *cmd)
{
	int	a;
	int i = 0;

	while (cmd && (i + 1))
	{
		printf("********\n%d eme commande\n", i++ + 1);
		printf("cmd_tmp:%s-\n", cmd->cmd_tmp);
		printf("path_cmd:%s\n", cmd->path_cmd);
		a = 0;
		if (!cmd->cmd_with_flags)
			printf("cmd with flag:%s-\n", "NULL");
		while (cmd->cmd_with_flags && cmd->cmd_with_flags[a])
			printf("cmd with flag:%s-\n", cmd->cmd_with_flags[a++]);
		printf("infile:%s-\n", cmd->infile);
		printf("infileflag:%d\n", cmd->infileflag);
		printf("infile fd:%d\n", cmd->infile_fd);
		printf("outfile:%s-\n", cmd->outfile);
		printf("outfileflag:%d\n", cmd->outfileflag);
		printf("outfile fd:%d\n", cmd->outfile_fd);
		printf("address cmd: %p\n", cmd);
		printf("address previous: %p\n", cmd->previous);
		printf("address next: %p\n", cmd->next);
		printf("********\n");
		cmd = cmd->next;
	}
}

int	in_out_fd(t_list *list_cmds, int *fd)
{
	int	infile;
	int outfile;

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

// static void	fd_value_exchange(int fd[], int temp_fd[])
// {
// 	temp_fd[1] = fd[0];
// 	fd[0] = temp_fd[0];
// 	temp_fd[0] = temp_fd[1];
// }

int	pipex(t_list *list_cmds, t_msvar *ms_env)
{
	int			fd[2];

	fd[0] = -1;
	fd[1] = -1;
	while (list_cmds)
	{
		if (list_cmds->next)
		{
			if (pipe(fd) == -1 && printf("Pipe error\n"))
				break;
		}
		if (one_cmd(list_cmds, ms_env, fd))
			return (1);
		list_cmds = list_cmds->next;
		if (list_cmds)
			list_cmds->infile_fd = dup(fd[0]);
		close(fd[0]);
		close(fd[1]);
	}
	return (0);
}

int	ft_pipe(char *cmdline, t_msvar *ms_env)
{
	t_list	*cmd_list;

	if(g_sig.sigint == 1)
	{
		return(g_sig.exit_status);
	}
	cmd_list = list_cmds(cmdline, ms_env);
	checklistcmd(cmd_list);
	if (cmd_list == NULL)
	{
		printf("error with cmds listing\n");
		return (1);
	}
	if (pipex(cmd_list, ms_env))
	{
		del_list(cmd_list);
		return(1);
	}
	del_list(cmd_list);
	return (0);
}

