/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:43:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/06 16:58:38 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(char **path, char *cmd)
{
	char	*temp_cmd;
	int		i;

	i = 0;
	// printf("cmd_path\n");
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
		if (cmds->cmd_with_flags[0][0] == '/'
			|| checkbuiltin(cmds->cmd_with_flags[0]))
			cmds->path_cmd = cmds->cmd_with_flags[0];
		else if (cmds->cmd_with_flags
			&& cmds->cmd_with_flags[0][0] != '/')
		{
			cmds->path_cmd = cmd_path(ms_env->all_path,
				cmds->cmd_with_flags[0]);
			if (cmds->path_cmd == NULL)
			{
				printf("error: command not found: %s\n",
					cmds->cmd_with_flags[0]);
				ft_cmd_error(cmds, 1);
				return (1);
			}
		}
		if (cmds->cmd_with_flags[1][0] == '$')
		{
			printf("$\n");
			cmds->cmd_with_flags[1] = dollar_data(cmds->cmd_with_flags[1], 0, ms_env);
		}
		cmds = cmds->next;
	}
	return (0);
}

void	ft_fillcmd_flag(t_list *cmds)
{
	while (cmds)
	{
		ft_clean_cmdline(cmds);
		printf("********\ncmd_tmp2:%s-\n", cmds->cmd_tmp);
		if (cmds->cmd_tmp[0] != 0 /*&& checknoecho(cmds) */)
		{
			printf("fillcmd_flag\n");
			cmds->cmd_with_flags = ft_splitcmd(cmds->cmd_tmp);
		}
		// printf("cmds->next = %p\n", cmds->next);
		cmds = cmds->next;
	}
}
