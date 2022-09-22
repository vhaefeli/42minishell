#include "../../includes/minishell.h"

int ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->value,1);
		env = env->next;
	}

	if (env)
		ft_putendl_fd(env->value,1);
	return (0);
}
