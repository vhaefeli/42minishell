/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:32:32 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/04 13:48:47 by vhaefeli         ###   ########.fr       */
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

void	check_file(char **argv)
{
	int	i;
	int	file;

	i = 4;
	if (access(argv[1], F_OK) != 0)
	{
		ft_printf("(Error) %s : %s \n", strerror(errno), argv[1]);
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], R_OK) != 0)
	{
		ft_printf("(Error) %s : %s \n", strerror(errno), argv[1]);
		exit(EXIT_FAILURE);
	}
	while (argv[i + 1])
		i++;
	if (access(argv[i], F_OK) != 0)
	{
		file = open(argv[i], O_CREAT, 0644);
		close(file);
	}
	if (access(argv[i], W_OK) != 0)
	{
		ft_printf("(Error) %s : %s \n", strerror(errno), argv[i]);
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
