/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:16:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/08 13:48:52 by vhaefeli         ###   ########.fr       */
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
		return(NULL);
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	all_path = ft_split(path, ':');
	free(path);
	return (all_path);
}

t_msvar	*ini_ms(void)
{
	t_msvar	*msvar;

	msvar = malloc(sizeof(t_msvar));
	msvar->envp_ms = NULL;
	msvar->exit = 0;
	return (msvar);
}

int	update_msenv(t_msvar *envp)
{
	int		lstsize;
	int		i;
	t_env	*temp;
	t_env	*temp2;

	i = 0;
	lstsize = 1;
	temp = envp->env;
	temp2 = envp->env;
	while (temp->next)
	{
		temp = temp->next;
		lstsize++;
	}
	del_tab(envp->envp_ms);
	envp->envp_ms = malloc(sizeof(char *) * (lstsize + 1));
	while (envp->env)
	{
		envp->envp_ms[i] = ft_strdup(envp->env->value);
		envp->env = envp->env->next;
		i++;
	}
	envp->envp_ms[i] = NULL;
	envp->env = temp2;
	return (1);
}
