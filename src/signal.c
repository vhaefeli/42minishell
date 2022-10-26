/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlefebvr <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:44:04 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/10/19 10:44:10 by tlefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (code == SIGINT)
	{
		rl_replace_line("",0);
		//ft_putstr_fd("\b\b  ", 1);
		ft_putstr_fd("\n", 1);
		//ft_putstr_fd(getcwd (NULL, 0), 2);
		//ft_putstr_fd(" ➜ minishell: ", 1);
		rl_on_new_line();
		rl_redisplay();
		g_sig.exit_status = 1;
	}
	g_sig.sigint = 1;
}
void	sig_quit(int code)
{
	//char	*nbr;

	//nbr = ft_itoa(code);
	if (code == SIGQUIT)
	{
		
		//ft_putstr_fd("Quit: ", 2);
		//ft_putendl_fd(nbr, 2);
		//g_sig.exit_status = 131;
		g_sig.sigquit = 1;
		//ft_putstr_fd(getcwd (NULL, 0), 2);
		//rl_on_new_line();
		//rl_redisplay();
	}

		rl_redisplay();
		//ft_putstr_fd("", 2);
	//ft_memdel(nbr);
}

void	hide_keystrokes(struct termios *saved)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, saved);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &attr);
}

void	sig_init(struct termios *saved)
{
	hide_keystrokes(saved);
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

