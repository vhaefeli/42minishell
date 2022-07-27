/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:48:06 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/25 22:26:38 by vhaefeli         ###   ########.fr       */
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
	char			*cmd_tmp;
	char			**cmd_with_flags;
	char			*infile;
	int				infileflag;//0 no infile / 1 infile / 2 heredoc as infile
	char			*outfile;
	int				outfileflag;//0 no outfile / 1 outfile O_TRUNC / 2 outfile O_APPEND
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

typedef	struct s_varchar
{
	int		i;
	int		j;
	char	*str;
	char	*str2;
} t_varchar;

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

// ft_splitcmd1.c and ft_splitcmd1.c used to split the string 
// with the complete commande in a table
int		quotesize(char *s, int i, char quotetype);
int		ft_cntcmdline(char *s);
int		ft_cntchar(char *s, int i);
void	ft_writequote(t_varchar *listcmd, int j);
char	*cpycmdflag(t_varchar *listcmd);
char	**ft_filltab(char *s, int nbline);
char	**ft_splitcmd(char *s);

#endif