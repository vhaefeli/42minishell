#include "../../includes/minishell.h"

void cmd_exit(t_msvar *msvar, char **cmd)
{
	msvar->exit = 1;
	ft_putstr_fd("exit ", 2);
	cmd[1] ? ft_putendl_fd("❤️", 2) : ft_putendl_fd("💚", 2);
	if (cmd[1] && cmd[2])
	{
		msvar->ret =1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		msvar->ret = 1;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (cmd[1])
		msvar->ret = ft_atoi(cmd[1]);
	else
		msvar->ret = 0;
}

int ft_exit(t_msvar *msvar)
{
	msvar->exit = 1;
	return(0);
}
