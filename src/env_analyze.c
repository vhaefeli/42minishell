/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:16:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/11 15:25:39 by vhaefeli         ###   ########.fr       */
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
		return (NULL);
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	all_path = ft_split(path, ':');
	free(path);
	return (all_path);
}

void	ini_ms(t_msvar	*msvar)
{
<<<<<<< HEAD
	t_msvar	*msvar;
	msvar = malloc(sizeof(t_msvar));
=======
>>>>>>> 0a4816bce6dd5c0efc32fd2e1936df664142aee7
	msvar->envp_ms = NULL;
	msvar->env = NULL;
	msvar->ret = 0;
	msvar->exit = 0;
	msvar->nbrofcmds = 0;
}

int	update_msenv(t_msvar *envp)
{
	int		lstsize;
	int		i;
	t_env	*temp;

	i = 0;
	lstsize = 1;
	temp = envp->env;
	while (temp && temp->next)
	{
		temp = temp->next;
		lstsize++;
	}
	temp = envp->env;
	del_tab(envp->envp_ms);
	envp->envp_ms = malloc(sizeof(char *) * (lstsize + 1));
	while (temp)
	{
		envp->envp_ms[i] = ft_strdup(temp->value);
		temp = temp->next;
		i++;
	}
	envp->envp_ms[i] = NULL;
	return (0);
}
