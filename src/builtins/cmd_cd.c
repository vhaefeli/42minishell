#include "../../includes/minishell.h"

static void print_error(char **args)
{
	ft_putstr_fd("cd ",2);
	if(args[2])
		ft_putstr_fd("string not in pwd: ",2);
	else
	{
		ft_putstr_fd(strerror(errno),2);
		ft_putstr_fd(": ",2);
	}
	ft_putendl_fd(args[1], 2);
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char *oldpwd;
	int i;
	int j;
	int s_alloc;

	while(env && env->next != NULL)
	{
		if(ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			if(!(oldpwd = malloc(sizeof(char) * s_alloc + 1)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if(i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}

	return (NULL);
}

static int		update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;
	printf("\nupdate pwd");
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	printf("\n update_OldPWD :%s",oldpwd);
	printf("\nsucces update pwd");
	return (0);
}

static int		go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	printf("\n go_to_path 1");
	env_path = NULL;
	if (option == 0)
	{
		printf("\ndans go to path HOME");
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 2);
		if (!env_path)
		{
			printf("pas de changement home set");
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		}
		if (!env_path)
		{
			printf("pas de changement de dossier");
			return (1);
		}
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (1);
		update_oldpwd(env);
	}
	printf("\n go_to_path env_path %s",env_path);
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int				cmd_cd(char **args, t_env *env)
{
	int		cd_ret;
	char	*new_dir;

	if (!args[1])
		return (go_to_path(0, env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		printf("\n ARGS2 =%s",args[1]);
		update_oldpwd(env);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			print_error(args);
	}
	return (cd_ret);
}