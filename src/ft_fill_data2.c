/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:43:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/18 18:48:39 by vhaefeli         ###   ########.fr       */
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

void	programm_to_execute(t_list	*cmds, t_msvar *ms_env)
{
	char	*tempstr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (cmds->cmd_with_flags[0][0] == '.' &&
		cmds->cmd_with_flags[0][1] == '/')
	{
		tempstr = get_env_value("PWD", ms_env->env);
		cmds->path_cmd = malloc(ft_strlen(tempstr)
			+ ft_strlen(cmds->cmd_with_flags[0]));
		while(tempstr[i])
			cmds->path_cmd[j++] = tempstr[i++];
		i = 1;
		while(cmds->cmd_with_flags[0][i])
			cmds->path_cmd[j++] = cmds->cmd_with_flags[0][i++];
		free (tempstr);
		tempstr = ft_strdup(cmds->cmd_with_flags[0]);
		free (cmds->cmd_with_flags[0]);
		cmds->cmd_with_flags[0] = ft_strcpyfrom(tempstr,2);
		free (tempstr);
	}
	// printf("cmds->cmd_with_flags[0]:%s-\n", cmds->cmd_with_flags[0]);
}

int	ft_fillpath_cmd(t_list *cmds, t_msvar *ms_env)
{
	if (cmds->cmd_with_flags[0][0] == '/'
		|| checkbuiltin(cmds->cmd_with_flags[0]))
		cmds->path_cmd = cmds->cmd_with_flags[0];
	else if (cmds->cmd_with_flags[0][0] == '.' &&
		cmds->cmd_with_flags[0][1] == '/')
		programm_to_execute(cmds, ms_env);
	else if (cmds->cmd_with_flags)
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
	return (0);
}

void	ft_fillcmd_flag(t_list *cmds, t_msvar *env)
{
	while (cmds)
	{
		ft_clean_cmdline(cmds);
		// printf("********\ncmd_tmp2:%s-\n", cmds->cmd_tmp);
		if (cmds->cmd_tmp[0] != 0)
		{
			// printf("fillcmd_flag\n");
			cmds->cmd_with_flags = ft_splitcmd(cmds->cmd_tmp, env);
		}
		// printf("cmds->next = %p\n", cmds->next);
		cmds = cmds->next;
	}
}
