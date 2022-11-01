/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:16:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/20 13:23:35 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("(Error) PATH not found\n");
		exit(EXIT_FAILURE);
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	all_path = ft_split(path, ':');
	free(path);
	return (all_path);
}

t_msvar	*ini_ms(char **envp)
{
	t_msvar *msvar;
	int		i;

	i = 0;
	msvar = malloc(sizeof(t_msvar));
	msvar->envp_origin = envp;
	// printf("ft_strlen(*envp): %zu\n", ft_strlen(*envp));
	msvar->envp_ms = malloc (sizeof(char *) * ft_strlen(*envp));
	while (envp[i])
	{
		msvar->envp_ms[i] = ft_strdup(envp[i]);
		// printf("msvar->envp_ms[i]:%s-\n", msvar->envp_ms[i]);
		i++;
	}
	msvar->all_path = path_finder(envp);
	msvar->exit = 0;
	msvar->stdin_fd = dup(STDIN_FILENO);
	msvar->stdout_fd = dup(STDOUT_FILENO);
	return (msvar);
}
