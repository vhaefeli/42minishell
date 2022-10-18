/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/18 15:39:31 by vhaefeli         ###   ########.fr       */
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
		printf("outfile:%s-\n", cmd->outfile);
		printf("outfileflag:%d\n", cmd->outfileflag);
		printf("address cmd: %p\n", cmd);
		printf("address previous: %p\n", cmd->previous);
		printf("address next: %p\n", cmd->next);
		printf("********\n");
		cmd = cmd->next;
	}
}

// static void	fd_value_exchange(int fd[], int temp_fd[])
// {
// 	if (temp_fd[0] != -1)
// 	{
// 		temp_fd[1] = fd[0];
// 		fd[0] = temp_fd[0];
// 		temp_fd[0] = temp_fd[1];
// 	}
// }

int	in_out_fd(t_list *list_cmds, t_msvar *ms_env, int *fd)
{
	int		infile;
	int		outfile;

	ft_fillpath_cmd(list_cmds, ms_env);
	infile = check_file_in(list_cmds, fd);
	outfile = check_file_out(list_cmds, fd);
	printf("path:%s\n", list_cmds->path_cmd);
	if (infile < 0 || outfile < 0)
	{
		close(fd[1]);
		close(fd[0]);
		perror("Fork");
		return (1);
	}
	printf("fd infile %d\n", infile);
	printf("fd outfile %d\n", outfile);
	if (infile > 2)
		dup2(infile, STDIN_FILENO);
	if (outfile > 2)
		dup2(outfile, STDOUT_FILENO);
	return (0);
}

void	pipex(t_list *list_cmds, t_msvar *ms_env)
{
	pid_t	pid1;
	int		fd[2];
	int		temp_fd[2];
	int		n_cmd;
	int		builtincmd_nb;

	n_cmd = 0;
	temp_fd[0] = -1;
	pid1 = -1;
	fd[0] = 0;
	fd[1] = 1;
	while (list_cmds && ++n_cmd)
	{
		if (list_cmds->next && pipe(fd) == -1)
		{
			perror("Pipe");
			break;
		}
		in_out_fd(list_cmds, ms_env, fd);
		builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
		printf("builtincmd_nb:%d\n",builtincmd_nb);
		if (builtincmd_nb)
		{
			printf("builtin\n");
			ms_env->ret = execbuiltin(list_cmds, builtincmd_nb, ms_env);
		}
		// fd_value_exchange(fd, temp_fd);
		// printf("after exchange) fd0 = %d , fd1 = %d \n", fd[0], fd[1]);
		if (!builtincmd_nb)
		{
			pid1 = fork();
			if (pid1 < 0 && printf("Fork %d : ", n_cmd))
				exit(1);
			if (pid1 == 0)
				child_process(list_cmds, fd, ms_env);
			waitpid(pid1, &ms_env->ret, 0);
		}
		// close(fd[1]);
		printf("fd0 = %d , fd1 = %d \n", fd[0], fd[1]);
		list_cmds = list_cmds->next;
	}
	close(fd[0]);
	while (n_cmd--)
		waitpid(pid1, &ms_env->ret, 0);
	if (access(".heredoc", F_OK) != 0)
		unlink(".heredoc");
	printf("end cmd\n");
}

int	ft_pipe(char *cmdline, t_msvar *ms_env)
{
	t_list	*cmd_list;

	printf("pipe cmdline:%s\n", cmdline);
	cmd_list = list_cmds(cmdline, ms_env);
	checklistcmd(cmd_list);
	if (cmd_list == NULL)
	{
		// printf("error with cmds listing\n");
		return (1);
	}
	if(g_sig.sigint == 1)
	{
		return(g_sig.exit_status);
	}
	pipex(cmd_list, ms_env);
	free(cmd_list);
	return (0);
}
