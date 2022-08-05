/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:43:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/05 23:36:45 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(char **path, char *cmd)
{
	char	*temp_cmd;
	int		i;

	i = 0;
	while (path[i])
	{
		temp_cmd = ft_strjoin("/", cmd);
		temp_cmd = ft_strjoin_free_s2(path[i], temp_cmd);
		if (access(temp_cmd, F_OK) == 0)
			return (temp_cmd);
		else
		{
			free(temp_cmd);
			i++;
		}
	}
	return (NULL);
}

int	ft_fillpath_cmd(t_list *cmds, t_msvar *ms_env)
{
	while (cmds)
	{
		cmds->path_cmd = cmd_path(ms_env->all_path, cmds->cmd_with_flags[0]);
		if (cmds->path_cmd == NULL)
		{
			printf("error: command not found: %s\n", cmds->cmd_with_flags[0]);
			ft_cmd_error(cmds, 1);
			return (1);
		}
		cmds = cmds->next;
	}
	return (0);
}

void	ft_fillcmd_flag(t_list *cmds)
{
	while (cmds)
	{
		cmds->cmd_with_flags = ft_splitcmd(cmds->cmd_tmp);
		cmds = cmds->next;
	}
}