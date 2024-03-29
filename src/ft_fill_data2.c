/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_data2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:43:46 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/15 14:47:40 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_path(char **path, char *cmd)
{
	char	*temp_cmd;
	int		i;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp_cmd = ft_strjoin("/", cmd);
		temp_cmd = ft_strjoin_free_s2(path[i], temp_cmd);
		if (access(temp_cmd, F_OK) == 0)
		{
			del_tab(path);
			return (temp_cmd);
		}
		else
		{
			free(temp_cmd);
			i++;
		}
	}
	del_tab(path);
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
		while (tempstr[i])
			cmds->path_cmd[j++] = tempstr[i++];
		i = 1;
		while (cmds->cmd_with_flags[0][i])
			cmds->path_cmd[j++] = cmds->cmd_with_flags[0][i++];
		free (tempstr);
		tempstr = ft_strdup(cmds->cmd_with_flags[0]);
		free (cmds->cmd_with_flags[0]);
		cmds->cmd_with_flags[0] = ft_strcpyfrom(tempstr, 2);
		free (tempstr);
	}
}

int	ft_fillpath_cmd(t_list *cmds, t_msvar *ms_env)
{
	if (cmds->cmd_with_flags[0][0] == '/'
		|| checkbuiltin(cmds->cmd_with_flags[0]))
		cmds->path_cmd = ft_strdup(cmds->cmd_with_flags[0]);
	else if (cmds->cmd_with_flags[0][0] == '.' &&
		cmds->cmd_with_flags[0][1] == '/')
		programm_to_execute(cmds, ms_env);
	else if (cmds->cmd_with_flags)
	{
		cmds->path_cmd = cmd_path(path_finder(ms_env->envp_ms),
				cmds->cmd_with_flags[0]);
		if (cmds->path_cmd == NULL)
		{
			printf("error: command not found: %s\n",
				cmds->cmd_with_flags[0]);
			ms_env->ret = 127;
			return (1);
		}
	}
	return (0);
}

void	ft_fillcmd_flag(t_list *cmds, t_msvar *env)
{
	env->nbrofcmds = 0;
	while (cmds)
	{
		env->nbrofcmds++;
		ft_clean_cmdline(cmds);
		if (cmds->cmd_tmp[0] != 0)
		{
			cmds->cmd_with_flags = ft_splitcmd(cmds->cmd_tmp, env);
		}
		cmds = cmds->next;
	}
}
