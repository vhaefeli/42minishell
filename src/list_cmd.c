/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:22:11 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/27 11:40:00 by vhaefeli         ###   ########.fr       */
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

// void	ft_error(t_list *list_cmds, char **path)
// {
// 	int	i;

// 	i = 0;
// 	while (list_cmds)
// 	{
// 		list_cmds = lst_delonecmd(list_cmds);
// 	}
// 	if (list_cmds)
// 		free(list_cmds);
// 	if (path)
// 	{
// 		while (path[i])
// 		{
// 			free(path[i]);
// 			i++;
// 		}
// 		free(path);
// 	}
// 	exit(EXIT_FAILURE);
// }

// t_list	*ft_lstnewcmd(char **path, char *cmd)
// {
// 	t_list	*list;
// 	int		i;

// 	i = 0;
// 	list = malloc(sizeof(*list));
// 	if (!list)
// 		return (NULL);
// 	list->cmd_with_flags = ft_split(cmd, ' ');
// 	list->path_cmd = cmd_path(path, list->cmd_with_flags[0]);
// 	if (list->path_cmd == NULL)
// 	{
// 		ft_printf("error: command not found: %s\n", list->cmd_with_flags[0]);
// 		while (list->cmd_with_flags[i])
// 		{
// 			free(list->cmd_with_flags[i]);
// 			list->cmd_with_flags[i++] = NULL;
// 		}
// 		free(list->cmd_with_flags);
// 		free(list);
// 		return (NULL);
// 	}
// 	list->infile = NULL;
// 	list->outfile = NULL;
// 	list->next = NULL;
// 	return (list);
// }

t_list	**list_cmds(char *cmdline, t_msvar **ms_env)
{
	t_list	*first_cmd;
	t_list	*new_cmd1;
	t_list	*new_cmd2;
	int		i;

	i = 0;
	// step 1 create the list with the correct nbr of elements
	first_cmd = ft_ininewlst_el();
	i = ft_pipe_split(cmdline, first_cmd, i);
	if (i >= 0 && cmdline[i] != 0)
		new_cmd1 = first_cmd;
	while (i >= 0 && cmdline[i] != 0)
	{
		new_cmd2 = ft_ininewlst_el();
		new_cmd2->previous = new_cmd1;
		new_cmd1->next = new_cmd2;
		i = ft_pipe_split(cmdline, new_cmd2, i);
		new_cmd1 = new_cmd2;
	}
	if (i = -1)
		return (NULL);
	// step 2 clean the cmds lines by searching the infile and outfile
	ft_in_out_files(&first_cmd);
	// step 3 fill the cmd_with_flag by a new split
	ft_fillcmd_flag(&first_cmd);
	// step 4 fill the path_cmd data
	ft_fillpath_cmd(&first_cmd, ms_env);
	free(cmdline);
	return (&first_cmd);
}
