/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:48:06 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/07/28 22:45:18 by vhaefeli         ###   ########.fr       */
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

// list_cmds.c create the chained list of cmds from the cmd line
t_list	**list_cmds(char *cmdline, t_msvar **ms_env);

// ft_pipe_split.c first op split the cmd line if there is pipes
int ft_pipe_split(char *cmdline, t_list *cmd, int i);

// ft_in_out_files.c check the infile and outfile and fill them in the list
size_t	check_infile(char *cmdline);
size_t	check_outfile(char *cmdline);
void	ft_check_in_out(t_list *cmd);
void	ft_in_out_files(t_list **cmds);

// ft_fill_data1.c et ft_fill_data2.c filling of the different data of
// chained list of commands
void	ft_fill_infile(t_list *cmd, size_t infile_len);
void	ft_fill_outfile(t_list *cmd, size_t outfile_len);
char	whosfirst(char *cmdline);
char	*ft_clean_cmdline(char *cmd_tmp, size_t cmdlen);
char	*cmd_path(char **path, char *cmd);
void	ft_fillpath_cmd(t_list **cmds, t_msvar *ms_env);
void	ft_fillcmd_flag(t_list **cmds);

// ft_splitcmd1.c and ft_splitcmd1.c used to split the string 
// with the complete commande in a table
int		quotesize(char *s, int i, char quotetype);
int		ft_cntcmdline(char *s);
int		ft_cntchar(char *s, int i);
void	ft_writequote(t_varchar *listcmd, int j);
char	*cpycmdflag(t_varchar *listcmd);
char	**ft_filltab(char *s, int nbline);
char	**ft_splitcmd(char *s);




// ft_error_exit.c list of the insid errors and their number
// exit of minishell
int		ft_cmd_error(t_list **list_cmds, int error_type);
void	ft_exit_minishell(char **path);

#endif