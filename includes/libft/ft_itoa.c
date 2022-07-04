/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:41:17 by vhaefeli          #+#    #+#             */
/*   Updated: 2021/11/02 11:45:38 by vhaefeli         ###   ########.fr       */
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

size_t	ft_ln(int n)
{
	size_t	l;

	l = 0;
	if (n <= 0)
		l = 1;
	while (n)
	{
		l++;
		n /= 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char			*nbr;
	unsigned long	nb;
	size_t			i;
	size_t			d;
	size_t			l;

	i = 0;
	l = ft_ln(n);
	nb = ft_inttolu(n);
	d = ft_unitp10(nb);
	nbr = malloc(l + 1);
	if (!nbr)
		return (NULL);
	if (n < 0)
		nbr[i++] = '-';
	while (i < l)
	{
		nbr[i++] = '0' + ((nb / d) % 10);
		d = d / 10;
	}
	nbr[i] = '\0';
	return (nbr);
}
