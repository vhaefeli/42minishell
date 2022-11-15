/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_children_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:17:40 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/15 16:04:40 by vhaefeli         ###   ########.fr       */
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
	while (1)
	{
		text = readline("> ");
		if (!text || !ft_strcmp(text, cmd->infile))
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
	if (!ft_strcmp("echo", cmd))
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
	if (builtincmd_nb > 3 && cmds->cmd_pid == 0)
		return (0);
	if (builtincmd_nb == 1)
		return (cmd_echo(cmds->cmd_with_flags));
	if (builtincmd_nb == 5)
		return (cmd_cd(cmds->cmd_with_flags, ms_env));
	if (builtincmd_nb == 2)
		return (cmd_pwd(cmds->cmd_with_flags));
	if (builtincmd_nb == 6)
		return (ft_export(cmds->cmd_with_flags, ms_env));
	if (builtincmd_nb == 7)
		return (ft_unset(cmds->cmd_with_flags, ms_env));
	if (builtincmd_nb == 3)
		return (ft_env(ms_env->env));
	if (builtincmd_nb == 4)
		return (cmd_exit(ms_env, cmds->cmd_with_flags));
	else
		return (4);
}

int	one_cmd(t_list *list_cmds, t_msvar *ms_env, int *fd)
{
	int		builtincmd_nb;

	if (list_cmds->cmd_pid < 0 && printf("Fork error\n"))
		return (1);
	if (list_cmds->cmd_pid == 0)
	{
		builtincmd_nb = checkbuiltin(list_cmds->cmd_with_flags[0]);
		in_out_fd(list_cmds, fd);
		if (fd[0] > 2)
			close(fd[0]);
		if (fd[1] > 2)
			close(fd[1]);
		if (builtincmd_nb)
			exit(execbuiltin(list_cmds, builtincmd_nb, ms_env));
		else
		{
			execve(list_cmds->path_cmd, list_cmds->cmd_with_flags,
				ms_env->envp_ms);
			printf("error with execve\n");
		}
		exit (127);
	}
	return (0);
}

void	wait_all(t_list	*cmds, t_msvar *ms_env)
{
	while (cmds)
	{
		if (cmds->infile_fd > -1)
			close(cmds->infile_fd);
		if (cmds->outfile_fd > -1)
			close(cmds->outfile_fd);
		if (cmds->cmd_pid > 0)
		{
			g_sig.pid = cmds->cmd_pid;
			waitpid(cmds->cmd_pid, &ms_env->ret, 0);
			if (WIFSIGNALED(ms_env->ret))
			{
				if (WTERMSIG(ms_env->ret) == SIGQUIT)
					write(1, "Quit: 3\n", 8);
				else if (WTERMSIG(ms_env->ret) == SIGINT)
					write(1, "\n", 1);
				ms_env->ret = 128 + ms_env->ret;
			}
			if (WIFEXITED(ms_env->ret))
				ms_env->ret = WEXITSTATUS(ms_env->ret);
			g_sig.pid = 0;
		}
		cmds = cmds->next;
	}
}
