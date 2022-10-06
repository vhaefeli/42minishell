/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:42:13 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/06 17:45:28 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

cpyin->i = no_space(cmd->cmd_tmp, cpyin->i);
		while (cmd->cmd_tmp[cpyin->i] && cmd->cmd_tmp[cpyin->i] != ' ')
		{
			if (cmd->cmd_tmp[cpyin->i] == ('\"') || cmd->cmd_tmp[cpyin->i] == ('\''))
				cpy_text_noquote(cpyin);
			cmd->infile[cpyin->j++] = cmd->cmd_tmp[cpyin->i++];
		}
