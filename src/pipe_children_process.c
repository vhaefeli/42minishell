/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/09/01 14:04:25 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static char	*ft_heredoc(char *infile)
{
	return (infile);
}

static int	check_file_in(t_list *cmd, int *fd)
{
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
			return (open(cmd->infile, O_RDONLY));
		}
		if (cmd->infileflag == 2)
			return (open(ft_heredoc(cmd->infile), O_RDONLY));
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
			close(file);
		}
		if (access(cmd->outfile, W_OK) != 0)
		{
			printf("(Error) %s : %s \n", strerror(errno), cmd->outfile);
			return (-1);
		}
		if (cmd->outfileflag == 1)
			return (open(cmd->outfile, O_WRONLY | O_TRUNC));
		if (cmd->outfileflag == 2)
			return (open(cmd->outfile, O_WRONLY | O_APPEND));
	}
	return (fd[1]);
}

int	checkbuiltin(char *cmd)
{
	size_t	n;

	n = ft_strlen(cmd);
	if (!ft_strncmp("echo", cmd, n))
		return (1);
	if (!ft_strncmp("cd", cmd, n))
		return (2);
	if (!ft_strncmp("pwd", cmd, n))
		return (3);
	if (!ft_strncmp("export", cmd, n))
		return (4);
	if (!ft_strncmp("unset", cmd, n))
		return (5);
	if (!ft_strncmp("env", cmd, n))
		return (6);
	if (!ft_strncmp("exit", cmd, n))
		return (7);
	else
		return (0);
}

int	execbuiltin(t_list *cmds, int builtincmd_nb, t_msvar *ms_env)
{
	// fonction temp pour utiliser les variables:
	return (builtincmd_nb + cmds->infileflag + ms_env->cmd_historyfile);

	// if (builtincmd_nb == 1)
	// 	return (cmd_echo(cmds, ms_env));
	// if (builtincmd_nb == 2)
	// 	return (cmd_cd(cmds, ms_env));
	// if (builtincmd_nb == 3)
	// 	return (cmd_pwd(cmds, ms_env));
	// if (builtincmd_nb == 4)
	// 	return (cmd_export(cmds, ms_env));
	// if (builtincmd_nb == 5)
	// 	return (cmd_unset(cmds, ms_env));
	// if (builtincmd_nb == 6)
	// 	return (cmd_env(cmds, ms_env));
	// if (builtincmd_nb == 7)
	// 	return (cmd_exit(cmds, ms_env));
	// else
		// return (4); //cmd builtin error
}

int	child_process(t_list *list_cmds, int *fd, t_msvar *ms_env)
{
	int		infile;
	int		outfile;
	int		builtincmd_nb;

	infile = check_file_in(list_cmds, fd);
	outfile = check_file_out(list_cmds, fd);
	printf("fd[0] :%d\n", fd[0]);
	printf("fd[1] :%d\n", fd[0]);
	if (infile < 0 || outfile < 0)
	{
		printf("fd[0] :%d\n", fd[0]);
		printf("fd[1] :%d\n", fd[0]);
		close(fd[1]);
		close(fd[0]);
		perror("Forkdsdsd");
		return (3); // infile outfile error
	}
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	if (fd[0] > -1)
		close(fd[0]);
	if (fd[1] > -1)
		close(fd[1]);
	builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
	if (builtincmd_nb)
	{
		execbuiltin(list_cmds, builtincmd_nb, ms_env);
		exit (1);
	}
	else
		execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, ms_env->envp_ms);
	exit (1);
	return (2);
}
