/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:13:44 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/08 19:01:40 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// si le retour de readline est bien un char
char **cmd_tab(char *input)
{
	char **cmd_tab;

	cmd_tab = ft_split(input, ' ');
	return (cmd_tab);
}

