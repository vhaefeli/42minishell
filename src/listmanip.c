/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listmanip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:04:13 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/08 08:20:54 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstfirst(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->previous)
	{
		if (lst->cmd_with_flags)
			printf("first cmd>%s\n", lst->cmd_with_flags[0]);
		else
			printf("infile outfile sans cmd\n");
		lst = lst->previous;
	}
	return (lst);
}

void	ft_lstadd_back(t_list *firstcmd, t_list *new)
{
	t_list	*lastel;

	if (!new)
		return ;
	lastel = ft_lstlast(firstcmd);
	if (!lastel)
		firstcmd = new;
	else
	{
		lastel->next = new;
		new->previous = lastel;
	}
}

t_list	*ft_ininewlst_el(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	printf("list el pos>%p\n", list);
	if (!list)
		return (NULL);
	list->infile = NULL;
	list->infileflag = 0;
	list->infile_fd = -1;
	list->outfile = NULL;
	list->outfileflag = 0;
	list->outfile_fd = -1;
	list->previous = NULL;
	list->next = NULL;
	list->cmd_with_flags = NULL;
	list->path_cmd = NULL;
	list->cmd_pid = -1;
	return (list);
}
