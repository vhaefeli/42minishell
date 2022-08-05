#include "minishell.h"

static int count_args(char **args)
{
	int	count;

	count = 0;
	while (args [count])
		count += 1;
	return (count);
}

static void	set_dir(char **env, char *name)
{
	char **arg;

	arg = (char **)ft_memalloc(sizeof(char *)* 4);
	arg[0] = NULL;
	arg[1] = ft_strdup("PWD");
	arg[2] = ft_strnew(PATH_MAX);
	arg[3] = 0;
	getcwd(arg[2], PATH_MAX);
	cmd_setenv(arg, env, name);
	free(arg[1]);
	free(arg[2]);
	free(arg);
	return ;
}

static void	access_dir(char **env, char *path)
{
	char		*msg;
	struct stat	stt;

	msg = NULL;
	if(!(access(path, F_OK) == -1))
		lstat(path, &stt);
	else
		msg = CD_NOTEXIST;
	if (!(access(path, R_OK) != -1))
		msg = CD_NOPERM;
	if (!S_ISDIR(stt.st_mode))
		msg = CD_NOTDIR;
	if(msg)
		ft_putendl(msg);
	else
	{
		set_dir(env, "OLDPWD");
		chdir(path);		
	}
	return;
}

char	**cmd_cd(char **a, char **env, char *name)
{
	int i;
	char p[PATH_MAX + 1];

	i = -1;
	while (++i < PATH_MAX)
		p[i] = 0;
	if (count_args(a) < 3)
	{
		(a)++;
		if(!*a || !ft_strcmp(*a, "~") \
			|| ((*a)[0] == '~' && (*a)[1] == '/'))
			ft_strcat(p, ft_find_env("~", env));
		if (*a && (*a)[0] == '~' && (*a)[1] == '/' \
			&& ft_strlen(*a) > 2)
			ft_strncat(p, (*a + 1), ft_strlen(*a));
		else if (*a && !ft_strcmp(*a, "-"))
			ft_putendl(ft_strcat(p, ft_find_env("$OLDPWD", env)));
		else if (*a && (*a)[0] != '~' && (*a)[0] != '-')
			ft_


	

	}


}
