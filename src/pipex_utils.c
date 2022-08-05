/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/04 23:01:52 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_nbargv(int argc)
{
	if (argc < 5)
	{
		ft_printf("(Error) Too few arguments\n");
		exit(EXIT_FAILURE);
	}
}


static void	fd_value_exchange(int fd[], int temp_fd[])
{
	temp_fd[1] = fd[0];
	fd[0] = temp_fd[0];
	temp_fd[0] = temp_fd[1];
}

void	pipex(t_list **list_cmds, char **envp)
{
	pid_t		pid1;
	int			fd[2];
	int			temp_fd[2];
	int			n_cmd;

	n_cmd = 0;
	temp_fd[0] = -1;
	pid1 = -1;
	while (*list_cmds && ++n_cmd)
	{
		if (pipe(fd) == -1 && ft_printf("Pipe %d : ", n_cmd))
			ft_error(*list_cmds, NULL);
		fd_value_exchange(fd, temp_fd);
		pid1 = fork();
		if (pid1 < 0 && ft_printf("Fork %d : ", n_cmd))
			ft_error(*list_cmds, NULL);
		if (pid1 == 0)
			child_process(*list_cmds, fd, envp);
		close(fd[1]);
		*list_cmds = lst_delonecmd(*list_cmds);
	}
	close(fd[0]);
	while (n_cmd--)
		waitpid(pid1, NULL, 0);
}
