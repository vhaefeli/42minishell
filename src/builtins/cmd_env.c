#include "minishell.h"

int ft_env(t_msvar *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl_fd(env->envp_ms,1);
		env = env->next;
	}

	if (env)
		ft_putendl_fd(end->envp_ms,1);
	return (0)
}
