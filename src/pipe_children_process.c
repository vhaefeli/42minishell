/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/05 15:55:52 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ft_heredoc(char *infile)
{
	int		file;
	char	*text;

	if (!infile)
	{
		printf("minishell: no end delimiter for heredoc");
		return (-1);
	}
	file = open(".heredoc", O_CREAT | O_RDWR | O_APPEND, 0666);
	while(1)
	{
		text = readline("> ");
		if (!ft_strcmp(text, infile))
			break ;
		write(file, text, ft_strlen(text));
		write(file, "\n", 1);
	}
	return (file);
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
			return (ft_heredoc(cmd->infile));
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

	if (builtincmd_nb == 1)
	 	return (ft_echo(cmds->cmd_with_flags));
	 if (builtincmd_nb == 2)
	 	return (cmd_cd(cmds->cmd_with_flags, ms_env->env));
	 if (builtincmd_nb == 3)
	 	return (cmd_pwd());
	//if (builtincmd_nb == 4)
	//	return (ft_export(cmds, ms_env, ms_env));
	//if (builtincmd_nb == 5)
	//	return (ft_unset(cmds, ms_env));
	if (builtincmd_nb == 6)
		return (ft_env(ms_env->env));
	if (builtincmd_nb == 7)
	{
	 	ft_exit(ms_env);
		return(0);
	}
	else
		return (4); //cmd builtin error
}

int	child_process(t_list *list_cmds, int *fd, t_msvar *ms_env)
{
	int		infile;
	int		outfile;
	int		builtincmd_nb;

	// printf("childprocess\n");
	infile = check_file_in(list_cmds, fd);
	outfile = check_file_out(list_cmds, fd);
	// printf("childprocessn");
	// printf("infile %d\n", infile);
	// printf("outfile %d\n", outfile);
	if (infile < 0 || outfile < 0)
	{
		close(fd[1]);
		close(fd[0]);
		perror("Fork");
		return (3); // infile outfile error
	}
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	// printf("childprocess2\n");
	// printf("fd[0]%d\n", fd[0]);
	// printf("fd[1]%d\n", fd[1]);
	if (fd[0] > -1)
		close(fd[0]);
	// printf("childprocess2a\n");
	if (fd[1] > -1)
		close(fd[1]);
	// printf("childprocess2b\n");
	if (list_cmds->cmd_with_flags[0] == NULL)
	{
		// printf("childprocess3\n");
		if (list_cmds->infileflag == 2)
			unlink(".heredoc");
		exit(1);
	}
	// printf("childprocess4\n");
	builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
	// printf("childprocess5\n");
	if (builtincmd_nb)
	{
		// printf("builtin cmd\n");
		execbuiltin(list_cmds, builtincmd_nb, ms_env);
		exit (1);
	}
	else
	{
		// printf("execve\n");
		execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, ms_env->envp_ms);
	}
	printf("error execve\n");
	exit (1);
	return (2);
}
