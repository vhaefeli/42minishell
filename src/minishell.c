/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/08/06 16:08:42 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pour control du bon fonctionnement = a effacer apres
void checklistcmd(t_list *cmd)
{
	int	a;
	int i = 0;

	while (cmd && (i + 1))
	{
		printf("********\n%d eme commande\n", i++ + 1);
		printf("path_cmd:%s\n", cmd->path_cmd);
		a = 0;
		while (cmd->cmd_with_flags[a])
			printf("cmd with flag:%s\n", cmd->cmd_with_flags[a++]);
		printf("infile:%s\n", cmd->infile);
		printf("infileflag:%d\n", cmd->infileflag);
		printf("outfile:%s\n", cmd->outfile);
		printf("outfileflag:%d\n", cmd->outfileflag);
		printf("address cmd: %p\n", &cmd);
		printf("address previous: %p\n", cmd->previous);
		printf("address next toujours: %p\n\n", cmd->next);
		cmd = cmd->next;
	}
}

int main (int argc, char **argv, char **envp)
{
	t_msvar *ms_env;
	t_list	*cmdslist;
	char	cmdline[32] = "< infile cat | wc -l >> outfile";

	printf("argc:%i argv0:%s\n", argc, argv[0]);
	printf("%s\n", cmdline);
	ms_env = ini_ms(envp);
	cmdslist = list_cmds(cmdline, ms_env);
	checklistcmd(cmdslist);
	printf("liste cree");
	del_list(cmdslist);
	checklistcmd(cmdslist);
    printf("liste vide");
    return (0);
}