
#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", 2);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
	ft_memdel(nbr);
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
