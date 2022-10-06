#include "minishell.h"

int ft_echo(char **args)
{
	int	nflag;

	if (!args[1])
	{
		printf("\n");
		return (0);
	}
	nflag = ft_strcmp(args[1], "-n");
	if (nflag)
		printf("%s\n", args[1]);
	else if (args[2])
		printf("%s", args[2]);
	return (0);
}

int	checknoecho(t_list *cmds)
{
	printf("1cmds->cmd_tmp %s\n", cmds->cmd_tmp);
	if (cmds->cmd_tmp[0] != 'e' && cmds->cmd_tmp[0] != 'E')
		return (1);
	if (cmds->cmd_tmp[1] != 'c' && cmds->cmd_tmp[1] != 'C')
		return (1);
	if (cmds->cmd_tmp[2] != 'h' && cmds->cmd_tmp[1] != 'H')
		return (1);
	if (cmds->cmd_tmp[3] != 'o' && cmds->cmd_tmp[1] != 'O')
		return (1);
	if (cmds->cmd_tmp[4] != ' ')
		return (1);
	fillechoflag(cmds);
	return (0);
}

void	fillechoflag(t_list *cmds)
{
	t_varchar	*text;
	char		*strtemp;
	int			nflag;

	printf("2cmds->cmd_tmp %s\n", cmds->cmd_tmp);
	nflag = chech_echo_flag(cmds);
	cmds->cmd_with_flags[0] = malloc(5);
	cmds->cmd_with_flags[0] = "echo";
	strtemp = malloc(ft_strlen(cmds->cmd_tmp));
	text = fillvarchar(cmds->cmd_tmp, strtemp, 4, 0);
	text->i = no_space(text->str, 4);
	if (nflag == 2)
		text->i+= 3;
	text->i = no_space(text->str, text->i);
	while (text->str[text->i])
	{
		if (text->str[text->i] == '\'' || text->str[text->i] == '\"')
			cpy_text_noquote(text);
		text->str2[text->j++] = text->str[text->i++];
	}
	text->str2[text->j] = 0;
	cmds->cmd_with_flags[nflag] = ft_strdup(text->str2);
	free(strtemp);
	free(text);
	cmds->cmd_with_flags[nflag + 1] = NULL;
}

int	chech_echo_flag(t_list *cmds)
{
	int	i;

	i = no_space(cmds->cmd_tmp, 4);
	if (cmds->cmd_tmp[i++] != '-')
	{
		cmds->cmd_with_flags = malloc(sizeof(char *) * 3);
		return (1);
	}
	if (cmds->cmd_tmp[i++] != 'n')
	{
		cmds->cmd_with_flags = malloc(sizeof(char *) * 3);
		return (1);
	}
	if (cmds->cmd_tmp[i] != ' ')
	{
		cmds->cmd_with_flags = malloc(sizeof(char *) * 3);
		return (1);
	}
	cmds->cmd_with_flags = malloc(sizeof(char *) * 4);
	cmds->cmd_with_flags[1] = malloc(3);
	cmds->cmd_with_flags[1] = "-n";
	return (2);
}