/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:22:11 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/08 19:01:40 by vhaefeli         ###   ########.fr       */
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

void	ft_error(t_list *list_cmds, char **path)
{
	int	i;

	i = 0;
	while (list_cmds)
	{
		list_cmds = lst_delonecmd(list_cmds);
	}
	if (list_cmds)
		free(list_cmds);
	if (path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	exit(EXIT_FAILURE);
}

t_list	*list_cmds(char **argv, char **envp)
{
	t_list	*new_cmd;
	t_list	*first_cmd;
	int		i;
	char	**path;

	path = path_finder(envp);
	first_cmd = ft_lstnewcmd(path, argv[2]);
	if (!first_cmd)
		ft_error(first_cmd, path);
	(first_cmd)->infile = argv[1];
	i = 3;
	while (argv[i + 1])
	{
		new_cmd = ft_lstnewcmd(path, argv[i]);
		if (new_cmd == NULL)
			ft_error(first_cmd, path);
		ft_lstadd_back(first_cmd, new_cmd);
		i++;
	}
	new_cmd->outfile = argv[i];
	i = 0;
	while (path[i])
		free(path[i++]);
	free(path);
	return (first_cmd);
}


t_list	*ft_lstnewcmd(char **path, char *cmd)
{
	t_list	*list;
	int		i;

	i = 0;
	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->cmd_with_flags = ft_split(cmd, ' ');
	list->path_cmd = cmd_path(path, list->cmd_with_flags[0]);
	if (list->path_cmd == NULL)
	{
		ft_printf("error: command not found: %s\n", list->cmd_with_flags[0]);
		while (list->cmd_with_flags[i])
		{
			free(list->cmd_with_flags[i]);
			list->cmd_with_flags[i++] = NULL;
		}
		free(list->cmd_with_flags);
		free(list);
		return (NULL);
	}
	list->infile = NULL;
	list->outfile = NULL;
	list->next = NULL;
	return (list);
}
