/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:22:11 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/04 23:44:45 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	**list_cmds(char *cmdline, t_msvar *ms_env)
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
		return (NULL); //error with the cmd
	// step 2 clean the cmds lines by searching the infile and outfile
	ft_in_out_files(&first_cmd);
	// step 3 fill the cmd_with_flag by a new split
	ft_fillcmd_flag(&first_cmd);
	// step 4 fill the path_cmd data
	ft_fillpath_cmd(&first_cmd, ms_env);
	free(cmdline);
	return (&first_cmd);
}
