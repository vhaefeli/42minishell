/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:07:34 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/07 18:47:09 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_varchar	*dollar_data(char *str, int i, t_msvar *env)
{
	char		*env_datatmp;
	t_varchar	*env_data;

	env_datatmp = malloc(1000);
	env_data = malloc(sizeof (t_varchar));
	env_data->j = 0;
	i++;
	while((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= 'a' && str[i] <= 'z'))
	{
		env_datatmp[env_data->j++] = str[i++];
	}
	env_datatmp[env_data->j] = 0;
	env_data->str = ft_strdup(env_datatmp);
	env_data->i = ft_strlen(env_data->str);
	env_data->str2 = get_env_path(env->secret_env,env_data->str, env_data->i);
	printf("get_env_path:%s\n", env_data->str2);
	env_data->j = ft_strlen(env_data->str2);
	free(env_datatmp);
	return(env_data);
}


		// if (cmds->cmd_with_flags[1][0] == '$')
		// {
		// 	printf("$\n");
		// 	cmds->cmd_with_flags[1] = dollar_data(cmds->cmd_with_flags[1], 0, ms_env);
		// }
