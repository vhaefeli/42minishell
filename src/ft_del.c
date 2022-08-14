/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 15:43:52 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/09 21:44:52 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int i;

	i = 0;
	if (!el)
		return ;
	while (el[i])
	{
		free(el[i]);
		el[i] = NULL;
		i++;
	}
	free(el);
	el = NULL;
}

void	del_list(t_list *list_cmds)
{
	t_list	*el1;
	t_list	*el2;

	if (!list_cmds)
		return ;
	printf("addresse listcmd: %p", list_cmds);
	printf("addresse &listcmd: %p", &list_cmds);
	el1 = ft_lstfirst(list_cmds);
	printf("addresse el1: %p", el1);
	printf("addresse el1: %p", &el1);
	while (el1)
	{

		del_el(el1->path_cmd);
		del_el(el1->cmd_tmp);
		del_tab(el1->cmd_with_flags);
		del_el(el1->infile);
		el1->infileflag = 0;
		del_el(el1->outfile);
		el1->outfileflag = 0;
		// a ete effacer avant
		el1->previous = NULL;
		el2 = el1;
		el1 = el1->next;
		free(el2);
	}
	// free (list_cmds);
	list_cmds = NULL;
}