/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:44:04 by tlefebvr          #+#    #+#             */
/*   Updated: 2022/11/03 16:43:46 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	if (g_sig.pid == 0)
	{
		if (code == SIGINT)
		{
			rl_replace_line("", 0);
			ft_putendl_fd("", 1);
			rl_on_new_line();
			rl_redisplay();
			g_sig.exit_status = 1;
		}
		else
		{
			rl_on_new_line();
			rl_redisplay();
		}
		if (code == SIGQUIT)
		{
			g_sig.sigquit = 1;
		}
	}
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
