#include "minishell.c"

int cmd_exit(t_list list, char **cmd)
{
	list->exit = 1;
	ft_putstr_fd("exit ", STDERR);
	cmd[1] ? ft_putendl_fd("❤️", STDERR) : ft_putendl_fd("💚", STDERR);
	if (cmd[1] && cmd[2])
	{
		//error
		ft_putendl_fd("minishell: exit: too many arguments", STDERR);
	}
	else if (cmd[1] && ft_strisnum(cmd[1]) == 0)
	{
		//error
		ft_putstr_fd("minishell: exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (cmd[1])
		//error 
	else
		mini->ret = 0;
}
