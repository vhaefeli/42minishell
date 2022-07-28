// plein de fonctions ecrite mais finalement pas utilisees. mais on sait jamais...



char **cmd_tab(char *input)
{
	char	**cmd_tab;
	
	cmd_tab = ft_splitcmd(input);
	return (cmd_tab);
}

char **allcmd(char *input)
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

void	ft_error(t_list *list_cmds, char **path)
{
	int	i;

	i = 0;
	while (list_cmds)
	{
		list_cmds = lst_delonecmd(list_cmds);
	}
	if (list_cmds)
		free(list_cmds);
	if (path)
	{
		while (path[i])
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
	exit(EXIT_FAILURE);
}

t_list	*ft_lstnewcmd(char **path, char *cmd)
{
	t_list	*list;
	int		i;

	i = 0;
	list = malloc(sizeof(*list));
	if (!list)
		return (NULL);
	list->cmd_with_flags = ft_split(cmd, ' ');
	list->path_cmd = cmd_path(path, list->cmd_with_flags[0]);
	if (list->path_cmd == NULL)
	{
		ft_printf("error: command not found: %s\n", list->cmd_with_flags[0]);
		while (list->cmd_with_flags[i])
		{
			free(list->cmd_with_flags[i]);
			list->cmd_with_flags[i++] = NULL;
		}
		free(list->cmd_with_flags);
		free(list);
		return (NULL);
	}
	list->infile = NULL;
	list->outfile = NULL;
	list->next = NULL;
	return (list);
}

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