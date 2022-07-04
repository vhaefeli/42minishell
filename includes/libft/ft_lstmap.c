/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:40:57 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/05 10:43:17 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
	t_list	*flst;
	t_list	*flsttemp;

	if (!lst)
		return (NULL);
	flst = ft_lstnew((f)(lst->content));
	if (!flst)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		flsttemp = ft_lstnew((f)(lst->content));
		if (!flsttemp)
		{
			ft_lstclear(&flst, (del));
			break ;
		}
		ft_lstadd_back(&flst, flsttemp);
	}	
	if (!flst)
		ft_lstclear(&flst, (del));
	return (flst);
}
