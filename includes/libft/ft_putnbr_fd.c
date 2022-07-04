/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:52:54 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/02 11:55:06 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long	ft_inttolu(int n)
{
	unsigned long	nb;

	if (n < 0)
		nb = -((unsigned long)n);
	else
		nb = (unsigned long)n;
	return (nb);
}

static unsigned long	ft_unitp10(unsigned long nb)
{
	unsigned long	d;

	d = 1;
	if (nb == 0)
		return (1);
	while (nb)
	{
		d *= 10;
		nb /= 10;
	}
	return (d / 10);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned long	d;
	unsigned long	nb;
	char			c;

	nb = ft_inttolu(n);
	d = ft_unitp10(nb);
	if (n < 0)
		write(fd, "-", 1);
	while (d)
	{
		c = '0' + ((nb / d) % 10);
		d /= 10;
		write(fd, &c, 1);
	}
}
