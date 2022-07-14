/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec_flag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:24:48 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/11 17:37:49 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "minishell.h"

int	ft_infile(t_list **cmd, char **cmd_tab)
{
	int	i;

	i = 1;
	if (cmd_tab[0][0] != '<')
		return (0);
	if (cmd_tab[0][1] == '<')
	{
		i++;
		*cmd->infileflag = 1;
	}
	if (cmd_tab[0][i] != '\0')
	{
		*cmd->infile = ft_strcpyfrom(cmd_tab[0], i);
		return (1);
	else
		*cmd->infile = cmd_tab[1];
	return (2);
}

int	ft_outfile(t_list **cmd, char **cmd_tab)
{
	int	i;
	int	j;

	j = tabsize(cmd_tab);
	i = ft_strlen(cmd_tab[j - 1]);
	if (i < 1 && cmd_tab[j - 1][(i - 1] != '>')
		return (0);
	if (i > 1 && cmd_tab[j - 1][i - 2] == '>')
	{
		*cmd->outfileflag = 1;
		if (i > 2)
		{
			*cmd->outfile = ft_strcpytill(cmd_tab[j - 1], i - 2);
			return (1);
		}
	}
	else if (i > 1)
	{
		*cmd->outfile = ft_strcpytill(cmd_tab[j - 1], i - 1);
		return (1);
	}
	else
		*cmd->outfile = cmd_tab[j - 2];
	return (2);
}
