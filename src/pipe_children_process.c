/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/14 12:08:21 by vhaefeli         ###   ########.fr       */
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

int	checkbuiltin(char *cmd)
{
	size_t	n;

	cmd = ft_strtolower(cmd);
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
	 	return (cmd_echo(cmds->cmd_with_flags));
	 if (builtincmd_nb == 2)
	 	return (cmd_cd(cmds->cmd_with_flags, ms_env->env));
	 if (builtincmd_nb == 3)
	 	return (cmd_pwd());
	 if (builtincmd_nb == 4)
	 	return (ft_export(cmds->cmd_with_flags, ms_env->env, ms_env->env));
	 if (builtincmd_nb == 5)
	 	return (ft_unset(cmds->cmd_with_flags, ms_env));
	if (builtincmd_nb == 6)
		return (ft_env(ms_env->env));
	if (builtincmd_nb == 7)
	{
		cmd_exit(ms_env,cmds->cmd_with_flags);
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
	int		a = 0;

	printf("child fd0 = %d , fd1 = %d \n", fd[0], fd[1]);

	printf("bloque?\n");
	if (list_cmds->cmd_with_flags[0] == NULL)
	{
		if (list_cmds->infileflag == 2)
			unlink(".heredoc");
		exit(0);
	}

	else
	{
		printf("execve\n");
		execve(list_cmds->path_cmd, list_cmds->cmd_with_flags, ms_env->envp_origin);
	}
	printf("error execve\n");
	exit (0);
	// return (2);
}
=
