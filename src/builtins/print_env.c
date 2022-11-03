/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlefebvr <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:45:52 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/10/18 11:45:54 by tlefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **tabl, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	i = 0;
	while (tabl[i] && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tabl[i], tabl[i + 1]) > 0)
			{
				tmp = tabl[i];
				tabl[i] = tabl[i + 1];
				tabl[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	free_tab(char **tabl)
{
	int	i;

	i = 0;
	while (tabl[i])
	{
		if (tabl[i])
			ft_memdel(tabl[i]);
		i++;
	}
	if (tabl)
		ft_memdel(tabl);
}

void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tabl;
	char	*str_env;

	str_env = env_to_str(env);
	tabl = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tabl, str_env_len(tabl));
	i = 0;
	while (tabl[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(tabl[i], 1);
		i--;
	}
	free_tab(tabl);
}
