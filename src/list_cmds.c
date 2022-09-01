/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:22:11 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/31 19:54:09 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*list_cmds(char *cmdline, t_msvar *ms_env)
{
	t_list	*first_cmd;
	t_list	*new_cmd1;
	t_list	*new_cmd2;
	int		i;

	i = 0;
	printf("cmdline:-%s-\n", cmdline);
	// step 1 create the list with the correct nbr of elements
	first_cmd = ft_ininewlst_el();
	i = ft_pipe_split(cmdline, first_cmd, i);
	if (i >= 0 && cmdline[i] != 0)
		new_cmd1 = first_cmd;
	while (i >= 0 && cmdline[i] != 0)
	{
		printf("listcmd i:%d\n", i);
		new_cmd2 = ft_ininewlst_el();
		new_cmd2->previous = new_cmd1;
		new_cmd1->next = new_cmd2;
		i = ft_pipe_split(cmdline, new_cmd2, i);
		printf("listcmd i:%d\n", i);
		new_cmd1 = new_cmd2;
	}
	if (i == -1)
		return (NULL); //error with the cmd
	// step 2 clean the cmds lines by searching the infile and outfile
	printf("list_cmds step2\n");
	ft_in_out_files(first_cmd);
	// step 3 fill the cmd_with_flag by a new split
	printf("list_cmds step3\n");
	ft_fillcmd_flag(first_cmd);
	// step 4 fill the path_cmd data
	printf("list_cmds step4\n");
	ft_fillpath_cmd(first_cmd, ms_env);
	printf("list_cmds end\n");
	// free(cmdline);  ' remettre quand cmdline ne sera pas le char * du main...
	return (first_cmd);
}
