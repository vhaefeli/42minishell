/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:33:40 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/15 15:09:34 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char		*oldpwd;
	t_varchar	*number;
	int			s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			number = fillvarchar(NULL, NULL, 0, 0);
			while (env->value[number->i++])
			{
				if (number->i > (int)len)
					oldpwd[number->j++] = env->value[number->i];
			}
			oldpwd[number->j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (1);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (0);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", 2);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", 2);
		if (!env_path)
			return (1);
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_memdel(env_path);
	return (ret);
}

int	cmd_cd(char **args, t_msvar *envp)
{
	int		cd_ret;

	if (!envp->env)
		return (1);
	if (!args[1])
		return (go_to_path(0, envp->env));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, envp->env);
	else
	{
		update_oldpwd(envp->env);
		cd_ret = chdir(args[1]);
		update_pwd(envp->env);
		if (cd_ret != 0)
			print_error(args);
	}
	if (cd_ret == -1)
	{
		envp->ret = 1;
		return (1);
	}
	return (cd_ret);
}
