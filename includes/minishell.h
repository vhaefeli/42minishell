/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:48:06 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/09/29 12:56:32 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "keys.h"
# include <stddef.h>
# include <stdlib.h>
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

#define BUFF_SIZE 4096

typedef struct s_list
{
	char			*path_cmd;
	char			*cmd_tmp;
	char			**cmd_with_flags; //table with in[0] the cmd and after the flags
	char			*infile;
	int				infileflag;//0 no infile / 1 infile / 2 heredoc as infile
	char			*outfile;
	int				outfileflag;//0 no outfile / 1 outfile O_TRUNC / 2 outfile O_APPEND
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct	s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_msvar
{
	char	**envp_origin;
	char	**envp_ms;
	t_env 	*env;
	t_env	*secret_env;
	int 	ret;
	int 	exit;
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

typedef struct	s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;
}				t_sig;

// // Builtins
// // cmd_cd.c
 int	ft_cd(char **args, t_env *env);

 // //cmd_echo.c
 int	ft_echo(char **args);

// // cmd_env.c
// int	ft_env(t_env *env);

// // cmd_exit.c
// void	cmd_exit(t_msvar *msvar, char **cmd);

// // cmd_export.c
// int	ft_export(char **args, t_env *env, t_env *secret);

int cmd_pwd(void);
int	ft_unset(char **a, t_msvar *msvar);

// // en_utils.c
 int		env_add(const char *value, t_env *env);
 char	*get_env_name(char *dest, const char *src);
 int		is_in_env(t_env *env, char *args);

// // env.c
 size_t	size_env(t_env *lst);
 char	*env_to_str(t_env *lst);
 int		env_init(t_msvar *msvar, char **env_array);
 int		secret_env_init(t_msvar *msvar, char **env_array);

// // get_env.c
 int		is_env_char(int c);
 int		is_valid_env(const char *env);
 int		env_value_len(const char *env);
 char	*env_value(char *env);
 char	*get_env_value(char *arg, t_env *env);

// // print_env.c
int 	str_env_len(char **env);
void 	sort_env(char **tabl, int env_len);
void  	print_sorted_env(t_env *env);

// env_analzye.c fonction using the original envp to find data
// and initialisation
t_msvar	*ini_ms(char **envp);
char	**path_finder(char **envp);

// listmanip.c fonctions to manipulate a list
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstfirst(t_list *lst);
void	ft_lstadd_back(t_list *firstcmd, t_list *new);
t_list	*ft_ininewlst_el(void);

// ft_del.c fonctions used to delete stuff
void	del_el(char *el);
void	del_tab(char **el);
void	del_list(t_list *list_cmds);

// list_cmds.c create the chained list of cmds from the cmd line
t_list	*list_cmds(char *cmdline, t_msvar *ms_env);

// ft_pipe_split.c first op split the cmd line if there is pipes
int ft_pipe_split(char *cmdline, t_list *cmd, int i);

// ft_in_out_files.c check the infile and outfile and fill them in the list
size_t	check_infile(char *cmdline);
size_t	check_outfile(char *cmdline);
void	ft_check_in_out(t_list *cmd);
void	ft_in_out_files(t_list *cmds);

// ft_fill_data1.c et ft_fill_data2.c filling of the different data of
// chained list of commands
void	ft_fill_infile(t_list *cmd, size_t infile_len);
void	ft_fill_outfile(t_list *cmd, size_t outfile_len);
void	cpy_between_cotes(char *src, char *dst, int *i, int *j);
int		no_space(char *src, int i);
void	ft_clean_cmdline(t_list *cmd);
char	*cmd_path(char **path, char *cmd);
int		ft_fillpath_cmd(t_list *cmds, t_msvar *ms_env);
void	ft_fillcmd_flag(t_list *cmds);

// ft_splitcmd1.c and ft_splitcmd1.c used to split the string
// with the complete commande in a table
int		quotesize(char *s, int i, char quotetype);
int		ft_cntcmdline(char *s);
int		ft_cntchar(char *s, char c, int i);
void	ft_writequote(t_varchar *listcmd, int j);
char	*cpycmdflag(t_varchar *listcmd);
size_t	size_between_spaces(char *s, int i);
char	**ft_filltab(char *s, int nbline);
char	**ft_splitcmd(char *s);

// pipe_children_process.c execute the commande
int		ft_heredoc(char *infile);
int		checkbuiltin(char *cmd);
int		execbuiltin(t_list *cmds, int builtincmd_nb, t_msvar *ms_env);
int		child_process(t_list *list_cmds, int fd[], t_msvar *ms_env);

// ft_error_exit.c list of the insid errors and their number
// exit of minishell
int		ft_cmd_error(t_list *list_cmds, int error_type);
int		ft_exit_minishell(t_msvar *ms_env);

// builtin cmds
// int		cmd_echo(t_list *cmds, char **envp);
// int		cmd_cd(t_list *cmds, char **envp);
// int		cmd_pwd(t_list *cmds, char **envp);
// int		cmd_export(t_list *cmds, char **envp);
// int		cmd_unset(t_list *cmds, char **envp);
// int		cmd_env(t_list *cmds, char **envp);
// int		cmd_exit(t_list *cmds, char **envp);

// ft_pipe_spit.c
int 	ft_pipe_split(char *cmdline, t_list *cmd, int i);

// pipe_utils.c
void	pipex(t_list **list_cmds, t_msvar *ms_env);
int		ft_pipe(char *cmdline, t_msvar *ms_env);

#endif
