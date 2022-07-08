/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:48:06 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/08 18:30:58 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "keys.h"
# include <stddef.h>
# include <stdlib.h>e
# include <stdio.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>

typedef struct s_list
{
	char			*path_cmd;
	char			**cmd_with_flags;
	char			*infile;
	int				infileflag;
	char			*outfile;
	int				outfileflag;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct s_msvar
{
	char	**envp_origin;
	char	**envp_ms;
	char	**all_path;
	int		cmd_historyfile;
	int		return_historyfile;
}	t_msvar;

// env_analzye.c fonction using the original envp to find data 
// and initialisation
t_msvar	ini_ms(char **envp);
char	**path_finder(char **envp);

// listmanip.c fonctions to manipulate a list
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfirst(t_list *lst);
void	ft_lstadd_back(t_list *firstcmd, t_list *new);
t_list	*ft_ininewlst_el(void);

// ft_del.c fonctions used to delete stuff
void	del_el(char *el);
void	del_tab(char **el);
void	del_list(t_list **list_cmds);

#endif