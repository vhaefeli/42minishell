/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:10:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/06/29 10:32:14 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_list	*cmd_list;

	check_nbargv(argc);
	check_file(argv);
	cmd_list = list_cmds(argv, envp);
	if (cmd_list == NULL)
	{
		ft_printf("error with cmds listing");
		return (1);
	}
	pipex(&cmd_list, envp);
	free(cmd_list);
	return (0);
}
