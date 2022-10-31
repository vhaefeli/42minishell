/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/30 16:11:33 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_sig g_sig;
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
	int	len;
	int	i;
	int	j;
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
	int i;

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


int main (int argc, char **argv, char **envp)
{
	t_msvar *ms_env;
	char	*cmdline;
	char	*place;

	(void)argv;
	if (argc != 1 && printf("Sorry, no flag allowed, try without any.\n"))
		return (1);
	ms_env = ini_ms(envp);
	welcometext();
	env_init(ms_env,envp);
	secret_env_init(ms_env,envp);
	increment_shell_level(ms_env->env);
	signal(SIGINT,&sig_int);
	signal(SIGQUIT,&sig_quit);
	while (ms_env->exit == 0)
	{
		place = last_name(getcwd(NULL,1));
		printf("%s",place);
		free(place);
		sig_init();
		cmdline = readline(" ➜ minishell: ");
		if (!cmdline)
			break ;
		if (g_sig.sigint != 1 && cmdline[0] != '\0'&& not_only_space(cmdline))
		{
				add_history(cmdline);
				ft_pipe(cmdline, ms_env);
		}
		del_el(cmdline);
	}
	free_env(ms_env->env);
	free_env(ms_env->secret_env);
	return (0);
}
