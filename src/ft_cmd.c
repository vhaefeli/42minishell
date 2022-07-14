/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:13:44 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/14 20:07:44 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "minishell.h"

// char **cmd_tab(char *input)
// {
// 	char	**cmd_tab;

// 	cmd_tab = ft_split(input, ' ');
// 	return (cmd_tab);
// }

char **cmd_tab(char *input)
{
	char	**cmd_tab;
	
	cmd_tab = ft_split(input, ' ');
	return (cmd_tab);
}

char **nbcmd(char *input)
{
	char	**cmds_tab;
	cmds_tab = ft_split(input, '|');
	return (cmds_tab);
}

int	tabsize(char **tab)
{
	int	n;

	n = 0;
	while (tab[n])
		n++;
	return (n);
}

t_list	*cmdlist_el(char *fullcmd)
{
	t_list	*cmd;
	char	**cmd_tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	cmd = ft_ininewlst_el();
	cmd_tab = cmd_tab(fullcmd);
	j = tabsize(cmd_tab);
	if (cmd_tab[i][0] == '<')
		i = i + ft_infile(&cmd, cmd_tab);
	if (cmd_tab[j - 1][(ft_strlen(cmd_tab[j - 1])) - 1] == '>')
		j = j - ft_outfile(&cmd, cmd_tab);
	while ( i <= j)
		cmd->cmd_with_flags[k++] = cmd_tab[i++];
	cmd->cmd_with_flags[k] = NULL;
	cmd->path_cmd = cmd_path(path, list->cmd_with_flags[0]);
	if (cmd->path_cmd == NULL)
	{
		ft_printf("error: command not found: %s\n", list->cmd_with_flags[0]);
		ft_cmd_error(&cmd, 1);
		return (NULL);
	}
	return (cmd);
}

t_list	**cmdslist(char **cmds_tab)
{
	t_list	*firstcmd;
	t_list	*newcmd;
	int		i;

	i = 1;
	firstcmd = cmdlist_el(cmds_tab[0]);
	if (firstcmd == NULL)
		return (NULL);
	while (cmds_tab[i])
	{
		newcmd = cmdlist_el(cmds_tab[i]);
		i++;
		if (newcmd == NULL)
		{
			ft_cmd_error(&firstcmd, 1);
			return (NULL);
		}
		ft_lstadd_back(&firstcmd, newcmd);
	}
	// pour control du bon fonctionnement = a effacer apres
	checklistcmd(&firstcmd);
	return (&firstcmd);
}

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