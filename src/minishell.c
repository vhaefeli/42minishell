/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:18:30 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/10/12 14:56:51 by vhaefeli         ###   ########.fr       */
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
char    last_name(char *str)
{
    int    len;
    int    i;
    int    j;
    char    *dst;

    len = ft_strlen(str);
    i = len - 1;
    j = 0;
    while (str[i] && str[i] != '/')
    {
        i--;
    }
    dst = malloc(len - i);
    i++;
    while (i < len)
    {
        dst[j++] = str[i++];
    }
    return (dst);
}

static char	*last_name(char *str)
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
	while (i < len)
	{
		dst[j++] = str[i++];
	}
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

	(void)argv;
	if (argc != 1 && printf("Sorry, no flag allowed, try without any.\n"))
		return (1);
	ms_env = ini_ms(envp);
	welcometext();
	env_init(ms_env,envp);
	secret_env_init(ms_env,envp);
	while (ms_env->exit == 0)
	{
		printf("%s",last_name(getcwd(NULL,1)));
		cmdline = readline(" ➜ minishell: ");
		if (!cmdline)
			break ;
		if (cmdline[0] != '\0'&& not_only_space(cmdline))
		{
			add_history(cmdline);
			ft_pipe(cmdline, ms_env);
		}
		free(cmdline);
		cmdline = NULL;
	}
	return (0);
}
