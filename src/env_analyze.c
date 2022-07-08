/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:16:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/08 18:49:32 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "minishell.h"

char	**path_finder(char **envp)
{
	int		i;
	char	*path;
	char	**all_path;

	i = 0;
	while (envp[i] && (ft_strnstr(envp[i], "PATH=", 5) == NULL))
		i++;
	if (envp[i] == NULL)
	{
		ft_printf("(Error) PATH not found\n");
		exit(EXIT_FAILURE);
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	all_path = ft_split(path, ':');
	free(path);
	return (all_path);
}

t_msvar	ini_ms(char **envp)
{
	t_msvar msvar;

	msvar->envp_origin = envp;
	msvar->envp_ms = envp;
	msvar->all_path = path_finder(envp);
	if (access("history_cmd", F_OK) != 0)
	{
		msvar->cmd_historyfile = open("history_cmd", O_CREAT | O_APPEND, 444);
	}
	if (access("history_cmd", W_OK) != 0 || access("history_cmd", R_OK) != 0)
	{
		ft_printf("(Error) %s : %s \n", strerror(errno), "history");
		exit(EXIT_FAILURE);
	}
	if (access("hist_return", F_OK) != 0)
	{
		msvar->return_historyfile = open("hist_return", O_CREAT 
		| O_APPEND, 444);
	}
	if (access("hist_return", W_OK) != 0 || access("hist_return", R_OK) != 0)
	{
		ft_printf("(Error) %s : %s \n", strerror(errno), "return history");
		exit(EXIT_FAILURE);
	}
	return (msvar);
}
