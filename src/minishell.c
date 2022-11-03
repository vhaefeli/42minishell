/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/03 10:25:03 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	welcometext(void)
{
	printf("\nW       W   EEEEEE   L       CCCC    OOOO      MM");
	printf("   MM   EEEEEE\n");
	printf("W       W   E        L     CC      OO    OO    M M M M   E\n");
	printf(" W  W  W    EEEE     L     C      O        O   M  M  M   EEEE\n");
	printf("  WW WW     E        L     CC      OO    OO    M     M   E\n");
	printf("  W   W     EEEEEE   LLLLL   CCCC    OOOO      M     M   EEEEEE\n");
	printf("\n");
}

char	*last_name(char *str)
{
	int		len;
	int		i;
	int		j;
	char	*dst;

	len = ft_strlen(str);
	i = len - 1;
	j = 0;
	while (str[i] && str[i] != '/')
	{
		i--;
	}
	dst = malloc(len - i);
	i++;
	while (i < len && str[i])
	{
		dst[j++] = str[i++];
	}
	dst[j] = 0;
	return (dst);
}

int	not_only_space(char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] == ' ')
	{
		i++;
	}
	if (!src[i])
		return (0);
	else
		return (1);
}

void	init_module(t_msvar *ms_env, char **envp)
{
	char			*cmdline;
	struct termios	saved;

	env_init (ms_env, envp);
	secret_env_init (ms_env, envp);
	increment_shell_level (ms_env->env);
	signal (SIGINT, &sig_int);
	signal (SIGQUIT, &sig_int);
	while (ms_env->exit == 0)
	{
		cmdline = readline(" ➜ minishell: ");
		if (!cmdline)
			break ;
		if (cmdline[0] != '\0' && not_only_space(cmdline))
		{
			sig_init(&saved);
			add_history(cmdline);
			ft_pipe(cmdline, ms_env);
			update_msenv(ms_env);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_msvar	*ms_env;

	(void)argv;
	if (argc != 1 && printf("Sorry, no flag allowed, try without any.\n"))
		return (1);
	ms_env = ini_ms(envp);
	welcometext();
	init_module(ms_env, envp);
	free_env (ms_env->env);
	free_env (ms_env->secret_env);
	del_tab(ms_env->envp_ms);
	free(ms_env);
	return (0);
}
