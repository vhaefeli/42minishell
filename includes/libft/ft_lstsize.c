/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:26:01 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/05 10:47:40 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	sizelst;

	sizelst = 1;
	if (!lst)
		return (0);
	while (lst->next)
	{
		sizelst++;
		lst = lst->next;
	}
	return (sizelst);
}
