/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/05 21:39:13 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_in(char *cmd_infile, int fd[])
{
	if (cmd_infile != NULL)
	{
		if (access(cmd_infile, F_OK) != 0)
		{
			printf("(Error) %s : %s \n", strerror(errno), cmd_infile);
			return (-1);
		}
		if (access(cmd_infile, R_OK) != 0)
		{
			printf("(Error) %s : %s \n", strerror(errno), cmd_infile);
			return (-1);
		}
		return (open(cmd_infile, O_RDONLY));
	}
	else
		return (fd[0]);
}

static int	check_file_out(char *cmd_outfile, int fd[])
{
	int	file;
	
	if (cmd_outfile != NULL)
	{
		if (access(cmd_outfile, F_OK) != 0)
		{
			file = open(cmd_outfile, O_CREAT, 0644);
			close(file);
		}
		if (access(cmd_outfile, W_OK) != 0)
		{
			printf("(Error) %s : %s \n", strerror(errno), cmd_outfile);
			return (-1);
		}
		return (open(cmd_outfile, O_WRONLY | O_TRUNC));
	}
	else
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

int	execbuiltin(t_list *cmds, int builtincmd_nb, char **envp)
{
	if (builtincmd_nb == 1)
		return (cmd_echo(cmds, envp));
	if (builtincmd_nb == 2)
		return (cmd_cd(cmds, envp));		
	if (builtincmd_nb == 3)
		return (cmd_pwd(cmds, envp));
	if (builtincmd_nb == 4)
		return (cmd_export(cmds, envp));
	if (builtincmd_nb == 5)
		return (cmd_unset(cmds, envp));
	if (builtincmd_nb == 6)
		return (cmd_env(cmds, envp));
	if (builtincmd_nb == 7)
		return (cmd_exit(cmds, envp));
	else
		return (4); //cmd builtin error
}

int	child_process(t_list *list_cmds, int fd[], char **envp)
{
	int		infile;
	int		outfile;
	int		builtincmd_nb;

	infile = check_file_in(list_cmds->infile, fd);
	outfile = check_file_out(list_cmds->outfile, fd);
	if (infile < 0 || outfile < 0)
	{
		close(fd[1]);
		close(fd[0]);
		perror("Fork");
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
		return (execbuiltin(list_cmds, builtincmd_nb, envp));
	else
		execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, envp);
		return (2); //cmd error
}