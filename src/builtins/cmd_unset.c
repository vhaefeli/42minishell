#include "minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void		free_node(t_msvar *msvar, t_env *env)
{
	if (msvar->env == env && env->next == NULL)
	{
		ft_memdel(msvar->env->value);
		msvar->env->value = NULL;
		msvar->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

int	ft_unset(char **a, t_msvar *msvar)
{
	t_env	*env;
	t_env	*tmp;

	env = msvar->env;
	if (!(a[1]))
		return (SUCCESS);
	if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
	{
		msvar->env = (env->next) ? env->next : msvar->env;
		free_node(msvar, env);
		return (SUCCESS);
	}
	while (env && env->next)
	{
		if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(msvar, env->next);
			env->next = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (SUCCESS);
}