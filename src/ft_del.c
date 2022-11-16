/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:43:52 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/16 11:56:24 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	checklistcmd(t_list *cmd)
// {
// 	int	a;
// 	int	i = 0;

// 	while (cmd && (i + 1))
// 	{
// 		printf("********\n%d eme commande\n", i++ + 1);
// 		printf("cmd_tmp:%s-\n", cmd->cmd_tmp);
// 		printf("path_cmd:%s\n", cmd->path_cmd);
// 		a = 0;
// 		if (!cmd->cmd_with_flags)
// 			printf("cmd with flag:%s-\n", "NULL");
// 		while (cmd->cmd_with_flags && cmd->cmd_with_flags[a])
// 			printf("cmd with flag:%s-\n", cmd->cmd_with_flags[a++]);
// 		printf("infile:%s-\n", cmd->infile);
// 		printf("infileflag:%d\n", cmd->infileflag);
// 		printf("infile fd:%d\n", cmd->infile_fd);
// 		printf("outfile:%s-\n", cmd->outfile);
// 		printf("outfileflag:%d\n", cmd->outfileflag);
// 		printf("outfile fd:%d\n", cmd->outfile_fd);
// 		printf("address cmd: %p\n", cmd);
// 		printf("address previous: %p\n", cmd->previous);
// 		printf("address next: %p\n", cmd->next);
// 		printf("********\n");
// 		cmd = cmd->next;
// 	}
// }

void	del_el(char *el)
{
	if (el)
	{
		free(el);
		el = NULL;
	}
}

void	del_tab(char **el)
{
	int	i;

	i = 0;
	if (!el)
		return ;
	while (el[i])
	{
		del_el(el[i]);
		i++;
	}
	if (el)
		free(el);
	el = NULL;
}

t_list	*del_list(t_list *list_cmds)
{
	t_list	*el1;
	t_list	*el2;

	if (!list_cmds)
		return (NULL);
	// checklistcmd(list_cmds);
	el1 = ft_lstfirst(list_cmds);
	while (el1)
	{
		del_el(el1->path_cmd);
		del_el(el1->cmd_tmp);
		del_tab(el1->cmd_with_flags);
		del_el(el1->infile);
		el1->infileflag = 0;
		del_el(el1->outfile);
		el1->outfileflag = 0;
		el1->previous = NULL;
		el2 = el1;
		el1 = el1->next;
		free(el2);
	}
	list_cmds = NULL;
	return (NULL);
}
