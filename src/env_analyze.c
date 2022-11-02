/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 17:16:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/02 14:56:45 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_msenv(t_msvar *envp)
{
	int		lstsize;
	int		i;
	t_env	*temp;

	i = 0;
	lstsize = 0;
	temp = envp->env;
	while (temp->next)
	{
		temp = temp->next;
		lstsize++;
	}
	printf("envp_ms avant update %p\n", envp->envp_ms);
	del_tab(envp->envp_ms);
	envp->envp_ms = malloc(sizeof(char*) * lstsize + 1);
	while (envp->env->next)
	{
		envp->envp_ms[i] = ft_strdup(envp->env->value);
		envp->env = envp->env->next;
		i++;
	}
	envp->envp_ms[i] = 0;
	printf("envp_ms apres update %p\n", envp->envp_ms);
}

char	**path_finder(char **envp)
{
	int		i;
	char	*path;
	char	**all_path;

	i = 0;
	while (envp[i])
	{
		// printf("envp[i] %s\n", envp[i]);
		i++;
	}
	i = 0;
	while (envp[i] && (ft_strnstr(envp[i], "PATH=", 5) == NULL))
		i++;
	if (envp[i] == NULL)
	{
		printf("(Error) PATH not found\n");
		return(char**)(NULL);
	}
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	all_path = ft_split(path, ':');
	free(path);
	return (all_path);
}

t_msvar	*ini_ms(char **envp)
{
	t_msvar	*msvar;
	int		i;

	i = 0;
	msvar = malloc(sizeof(t_msvar));
	msvar->envp_origin = envp;
	msvar->envp_ms = malloc (sizeof(char *) * ft_strlen(*envp) + 1);
	while (envp[i])
	{
		msvar->envp_ms[i] = ft_strdup(envp[i]);
		printf("Envp_ms[i] %s, %p\n", msvar->envp_ms[i], msvar->envp_ms[i]);
		i++;
	}
	msvar->envp_ms[i] = NULL;
	printf("envp_ms ini %p\n", msvar->envp_ms);
	msvar->exit = 0;
	return (msvar);
}
