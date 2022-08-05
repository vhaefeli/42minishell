#include "minishell.h"

char	**cmd_pwd(char **args, char **env, char *name)
{
	char	buf[PATH_MAX + 1];
	int		i;

	i = 0;
	while (args[i])
		i += 1;
	if (i > 1)
		ft_putendl("Too many arguments...");
	else if (i == 1)
		ft_putendl(getcwd(buf, PATH_MAX));
	return (env);
	(void)name;
}
