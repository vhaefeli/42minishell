/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkcmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:13:44 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/27 12:03:32 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "minishell.h"

// pour control du bon fonctionnement = a effacer apres
void checklistcmd(t_list **cmd)
{
	int	a;

	while (*cmd)
	{
		printf("%d eme commande\n", i)
		printf("path_cmd: %s\n", newcmd->path_cmd);
		a = 0;
		while (newcmd->cmd_with_flags[a])
			printf("path_cmd: %s\n", newcmd->cmd_with_flags[a++]);
		printf("infile: %s\n", newcmd->infile);
		printf("infileflag: %d\n", newcmd->infileflag);
		printf("outfile: %s\n", newcmd->outfile);
		printf("outfileflag: %d\n", newcmd->outfileflag);
		printf("address cmd: %p\n", &newcmd);
		printf("address previous: %p\n", newcmd->previous);
		printf("address next toujours: %p\n", newcmd->next);
	}
}