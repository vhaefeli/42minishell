/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/09/27 16:25:01 by vhaefeli         ###   ########.fr       */
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
			printf("cmd with flag:%s-\n", cmd->cmd_with_flags);
		while (cmd->cmd_with_flags && cmd->cmd_with_flags[a])
			printf("cmd with flag:%s-\n", cmd->cmd_with_flags[a++]);
		printf("infile:%s-\n", cmd->infile);
		printf("infileflag:%d\n", cmd->infileflag);
		printf("outfile:%s-\n", cmd->outfile);
		printf("outfileflag:%d\n", cmd->outfileflag);
		printf("address cmd: %p\n", cmd);
		printf("address previous: %p\n", cmd->previous);
		printf("address next: %p\n", cmd->next);
		printf("********\n\n");
		cmd = cmd->next;
	}
}

static void	fd_value_exchange(int fd[], int temp_fd[])
{
	temp_fd[1] = fd[0];
	fd[0] = temp_fd[0];
	temp_fd[0] = temp_fd[1];
}

void	pipex(t_list **list_cmds, t_msvar *ms_env)
{
	pid_t		pid1;
	int			fd[2];
	int			temp_fd[2];
	int			n_cmd;

	n_cmd = 0;
	temp_fd[0] = -1;
	pid1 = -1;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	printf("pipex\n");
	if(!(*list_cmds)->next)
	{
		printf("only one cmd\n");
		pid1 = fork();
		if (pid1 < 0 && printf("Fork %d : ", n_cmd))
			exit(0);
         // ft_error(*list_cmds, NULL);
		if (pid1 == 0)
			child_process(*list_cmds, fd, ms_env);
		waitpid(pid1, NULL, 0);
		close(fd[1]);
// a reactiver des que le heredoc est ok
		// if ((*list_cmds)->infileflag == 2)
		// 		unlink(".heredoc");
	}
	else
	{
		while (*list_cmds && ++n_cmd)
		{
			if (pipe(fd) == -1 && printf("Pipe %d : ", n_cmd))
				exit (0);
				// ft_error(*list_cmds, NULL);
			fd_value_exchange(fd, temp_fd);
			pid1 = fork();
			if (pid1 < 0 && printf("Fork %d : ", n_cmd))
				exit(0);
				// ft_error(*list_cmds, NULL);
			if (pid1 == 0)
				child_process(*list_cmds, fd, ms_env);
			waitpid(pid1, NULL, 0);
			close(fd[1]);
			*list_cmds = (*list_cmds)->next;
		}
// a reactiver des que le heredoc est ok
		// if ((*list_cmds)->infileflag == 2)
		// 	unlink(".heredoc");
		close(fd[0]);
		while (n_cmd--)
			waitpid(pid1, NULL, 0);
	}
}

int	ft_pipe(char *cmdline, t_msvar *ms_env)
{
	t_list	*cmd_list;

	printf("pipe cmdline:%s\n", cmdline);
	cmd_list = list_cmds(cmdline, ms_env);
	checklistcmd(cmd_list);
	if (cmd_list == NULL)
	{
		printf("error with cmds listing");
		return (1);
	}
	pipex(&cmd_list, ms_env);
	free(cmd_list);
	return (0);
}
