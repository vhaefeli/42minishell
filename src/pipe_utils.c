/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/17 23:25:48 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_in(t_list *cmd, int *fd)
{
	printf("infile %s\n", cmd->infile);
	if (cmd->infile != NULL)
	{
		if (cmd->infileflag == 1)
		{
			if (access(cmd->infile, F_OK) != 0)
			{
				printf("(Error) %s : %s \n", strerror(errno), cmd->infile);
				return (-1);
			}
			if (access(cmd->infile, R_OK) != 0)
			{
				printf("(Error) %s : %s \n", strerror(errno), cmd->infile);
				return (-1);
			}
			close (fd[0]);
			return (open(cmd->infile, O_RDONLY));
		}
		if (cmd->infileflag == 2)
			return (open(".heredoc", O_RDONLY));
	}
	return (fd[0]);
}

static int	check_file_out(t_list *cmd, int *fd)
{
	int	file;

	if (cmd->outfile != NULL)
	{
		if (access(cmd->outfile, F_OK) != 0)
		{
			file = open(cmd->outfile, O_CREAT, 0644);
			// close(file);
		}
		if (access(cmd->outfile, W_OK) != 0)
		{
			printf("(Error) %s : %s \n", strerror(errno), cmd->outfile);
			return (-1);
		}
		if (cmd->outfileflag == 1)
		{
			close(fd[1]);
			return (open(cmd->outfile, O_WRONLY | O_TRUNC));
		}
		if (cmd->outfileflag == 2)
		{
			close(fd[1]);
			return (open(cmd->outfile, O_WRONLY | O_APPEND));
		}
	}
	return (fd[1]);
}


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

static void	fd_value_exchange(int fd[], int temp_fd[])
{
	if (temp_fd[0] != -1)
	{
		temp_fd[1] = fd[0];
		fd[0] = temp_fd[0];
		temp_fd[0] = temp_fd[1];
	}
}

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
		return (perror("Fork"));
	}
	printf("infile %d\n", infile);
	printf("outfile %d\n", outfile);
	if (infile > 2)
	{
		dup2(infile, STDIN_FILENO);
	}
	if (outfile > 2)
	{
		dup2(outfile, STDOUT_FILENO);
	}
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
	printf("1) fd0(STDIN_FILENO) = %d , fd1(STDOUT_FILENO) = %d \n", fd[0], fd[1]);
	while (list_cmds && ++n_cmd)
	{
		in_out_fd(list_cmds, ms_env, fd);
		if (list_cmds->next && pipe(fd) == -1)
		{
			perror("Pipe");
			break;
		}
		builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
		if (builtincmd_nb)
		{
			printf("builtin\n");
			execbuiltin(list_cmds, builtincmd_nb, ms_env);
		}
		else
		if (list_cmds->next && pipe(fd) == -1 && printf("Pipe %d : ", n_cmd))
			perror("Pipe");
		printf("fd0 = %d , fd1 = %d \n", fd[0], fd[1]);
		fd_value_exchange(fd, temp_fd);
		// printf("after exchange) fd0 = %d , fd1 = %d \n", fd[0], fd[1]);
		pid1 = fork();
		if (pid1 < 0 && printf("Fork %d : ", n_cmd))
			exit(1);
		if (pid1 == 0)
			child_process(list_cmds, fd, ms_env);
		if (pid1 > 0)
			printf("master fd0 = %d , fd1 = %d \n", fd[0], fd[1]);
		waitpid(pid1, &ms_env->ret, 0);
		close(fd[1]);
		list_cmds = list_cmds->next;
	}
	close(fd[0]);
	while (n_cmd--)
		waitpid(pid1, &ms_env->ret, 0);
	if (access(".heredoc", F_OK) != 0)
		unlink(".heredoc");
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
	if(g_sig.sigint == 1)
	{
		return(g_sig.exit_status);
	}
	pipex(cmd_list, ms_env);
	free(cmd_list);
	return (0);
}
