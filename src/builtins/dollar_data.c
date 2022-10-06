/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:07:34 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/06 17:15:19 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_data(char *str, int i, t_msvar *env)
{
	char	*env_datatmp;
	char	*env_data;
	int		j;

	j = 0;
	env_datatmp = malloc(100);
	printf("str[i]:%c\n", str[i]);
	i++;
	while((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z'))
	{
		printf("str[i]:%c\n", str[i]);
		env_datatmp[j++] = str[i++];
	}
	env_datatmp[j] = 0;
	printf("env_datatmp %s\n", env_datatmp);
	env_data = get_env_path(env->secret_env, env_datatmp, ft_strlen(env_datatmp));
	printf("env_data %s\n", env_data);
	free(env_datatmp);
	free(str);
	return(env_data);
}
