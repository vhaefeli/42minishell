#include "minishell.h"

char		**cmd_env(char **args, char **env, char *name)
{
	int		i;

	i = -1;
	while (env[++i])
		ft_putendl(env[i]);
	return (env);
	(void)args;
	(void)name;
}
