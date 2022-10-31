/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/31 23:01:51 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_list *cmd)
{
	char	*text;

	if (!cmd->infile)
	{
		printf("minishell: no end delimiter for heredoc");
		return (-1);
	}
	if (access(".heredoc", F_OK) == 0)
	{
		unlink(".heredoc");
	}
	cmd->infile_fd = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0666);
	while(1)
	{
		text = readline("> ");
		if (!ft_strcmp(text, cmd->infile))
			break ;
		write(cmd->infile_fd, text, ft_strlen(text));
		write(cmd->infile_fd, "\n", 1);
	}
	close(cmd->infile_fd);
	return (0);
}

int	checkbuiltin(char *cmd)
{
	size_t	n;

	cmd = ft_strtolower(cmd);
	n = ft_strlen(cmd);
	if (!ft_strncmp("echo", cmd, n))
		return (1);
	if (!ft_strncmp("pwd", cmd, n))
		return (2);
	if (!ft_strncmp("env", cmd, n))
		return (3);
	if (!ft_strncmp("exit", cmd, n))
		return (4);
	if (!ft_strncmp("cd", cmd, n))
		return (5);
	if (!ft_strncmp("export", cmd, n))
		return (6);
	if (!ft_strncmp("unset", cmd, n))
		return (7);

	else
		return (0);
}

int	execbuiltin(t_list *cmds, int builtincmd_nb, t_msvar *ms_env)
{

	if (builtincmd_nb == 1)
	 	return (cmd_echo(cmds->cmd_with_flags));
	 if (builtincmd_nb == 5)
	 	return (cmd_cd(cmds->cmd_with_flags, ms_env->env));
	 if (builtincmd_nb == 2)
	 	return (cmd_pwd());
	 if (builtincmd_nb == 6)
	 	return (ft_export(cmds->cmd_with_flags, ms_env->env, ms_env->env));
	 if (builtincmd_nb == 7)
	 	return (ft_unset(cmds->cmd_with_flags, ms_env));
	if (builtincmd_nb == 3) 
		return (ft_env(ms_env->env));
	if (builtincmd_nb == 4)
	{
		cmd_exit(ms_env,cmds->cmd_with_flags);
		return(0);
	}
	else
		return (4); //cmd builtin error
}

int	one_cmd(t_list *list_cmds, t_msvar *ms_env, int *fd)
{
	int		builtincmd_nb;
	// int		pid;

	if (ft_fillpath_cmd(list_cmds, ms_env))
		return (1);
	// pid = fork();
	// if (pid < 0 && printf("Fork error\n"))
	// 	return (1);
	// if (pid == 0)
	// {
		builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
		in_out_fd(list_cmds, fd);
		if (list_cmds->next)
		{
			if (fd[0] > -1)
			close(fd[0]);
			if (fd[1] > -1)
			close(fd[1]);
		}
		if (builtincmd_nb)
			exit(execbuiltin(list_cmds, builtincmd_nb, ms_env));
		else
		{
			execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, ms_env->envp_origin);
			printf("error with execve");
			return (2);
		}
	// }
	// waitpid(pid, NULL, 0);
	return (0);
}

// int	child_process(t_list *list_cmds, int *fd, t_msvar *ms_env)
// {
// 	int		infile_fd;
// 	int		outfile_fd;
// 	int		builtincmd_nb;
// 	// int		a = 0;

// 	ft_fillpath_cmd(list_cmds, ms_env);
// 	infile_fd = check_file_in(list_cmds, fd);
// 	check_file_out(list_cmds, fd);
// 	close(f[0]);
// 	close(f[1]);


// 	// printf("path:%s\n", list_cmds->path_cmd);
// 	if (infile < 0 || outfile < 0)
// 	{
// 		close(fd[1]);
// 		close(fd[0]);
// 		perror("Fork");
// 		exit(0); // infile outfile error
// 	}
// 	// printf("infile %d\n", infile);
// 	// printf("outfile %d\n", outfile);
// 	if (infile > 2)
// 	{
// 		dup2(infile, STDIN_FILENO);
// 		close(infile);
// 	}
// 	if (outfile > 2)
// 	{
// 		dup2(outfile, STDOUT_FILENO);
// 		close(outfile);
// 	}
// 	if (list_cmds->cmd_with_flags[0] == NULL)
// 	{
// 		if (list_cmds->infileflag == 2)
// 			unlink(".heredoc");
// 		exit(0);
// 	}
// 	builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
// 	if (builtincmd_nb)
// 	{
// 		// printf("builtin\n");
// 		execbuiltin(list_cmds, builtincmd_nb, ms_env);
// 		exit (0);
// 	}
// 	else
// 	{
// 		// printf("execve\n");
// 		// printf("path_cmd:%s\n", list_cmds->path_cmd);
// 		// a = 0;
// 		// if (!list_cmds->cmd_with_flags)
// 		// 	printf("cmd with flag:%s-\n", "NULL");
// 		// while (list_cmds->cmd_with_flags && list_cmds->cmd_with_flags[a])
// 		// 	printf("cmd with flag:%s-\n", list_cmds->cmd_with_flags[a++]);
// 		// printf("infile:%s-\n", list_cmds->infile);
// 		// printf("infileflag:%d\n", list_cmds->infileflag);
// 		// printf("outfile:%s-\n", list_cmds->outfile);
// 		// printf("outfileflag:%d\n", list_cmds->outfileflag);
// 		// printf("********\n");
// 		execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, ms_env->envp_origin);
// 	}
// 	printf("error execve\n");
// 	exit (0);
// 	// return (2);
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// int main(int argc, char* argv[]) {
//     int fd[2];
//     if (pipe(fd) == -1) {
//         return;
//     }

//     int pid1 = fork();
//     if (pid < 0) {
//         return 2;
//     }

//     if (pid1 == 0) {
//         // Child process 1 (ping)
//         dup2(fd[1], STDOUT_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("ping", "ping", "-c", "5", "google.com", NULL);
//     }

//     int pid2 = fork();
//     if (pid2 < 0) {
//         return 3;
//     }

//     if (pid2 == 0) {
//         // Child process 2 (grep)
//         dup2(fd[0], STDIN_FILENO);
//         close(fd[0]);
//         close(fd[1]);
//         execlp("grep", "grep", "rtt", NULL);
//     }

// 	        close(fd[0]);
//         close(fd[1]);

//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);

//     return 0;
// }


// 		// ft_putstr_fd(list_cmds->cmd_with_flags[0], startfd[1]);
// 		// ft_putstr_fd("\n", startfd[1]);

// 		// printf("avant STDIN_FILENO = %d , STDOUT_FILENO = %d \n", STDIN_FILENO, STDOUT_FILENO);

// 		// printf("apres STDIN_FILENO = %d , STDOUT_FILENO = %d \n", STDIN_FILENO, STDOUT_FILENO);
// 		// ft_putstr_fd("STDIN_FILENO ", startfd[1]);
// 		// ft_putnbr_fd(STDIN_FILENO, startfd[1]);
// 		// ft_putstr_fd("\nSTDOUT_FILENO ", startfd[1]);
// 		// ft_putnbr_fd(STDOUT_FILENO, startfd[1]);
// 		// ft_putstr_fd("\n", startfd[1]);
