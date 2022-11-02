/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhaefeli <vhaefeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:48:06 by vhaefeli          #+#    #+#             */
/*   Updated: 2022/11/02 10:59:10 by vhaefeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <termios.h>

# define BUFF_SIZE 4096

typedef struct s_list
{
	char			*path_cmd;
	char			*cmd_tmp;
	char			**cmd_with_flags;
	char			*infile;
	int				infileflag;
	int				infile_fd;
	char			*outfile;
	int				outfileflag;
	int				outfile_fd;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_msvar
{
	char	**envp_origin;
	char	**envp_ms;
	t_env	*env;
	t_env	*secret_env;
	int		ret;
	int		prev_ret;
	int		exit;
	char	**all_path;
	int		stdin_fd;
	int		stdout_fd;
	int		nbrofcmds;
}	t_msvar;

typedef struct s_varchar
{
	int		i;
	int		j;
	char	*str;
	char	*str2;
}	t_varchar;

typedef struct s_sig
{
	int				sigint;
	int				sigquit;
	int				exit_status;
	pid_t			pid;

}				t_sig;

// Global
t_sig	g_sig;

// // Builtins
// // cmd_cd.c
char		*get_env_path(t_env *env, const char *var, size_t len);
int			cmd_cd(char **args, t_msvar *envp);
// //cmd_echo.c
int			cmd_echo(char **args);
// // cmd_env.c
int			ft_env(t_env *env);

// // cmd_exit.c
void		cmd_exit(t_msvar *msvar, char **cmd);
int			ft_exit(t_msvar *msvar);

// // signal.c
void		sig_init(struct termios *saved);
void		sig_quit(int code);
void		sig_int(int code);

// // cmd_export.c
int			ft_export(char **args, t_msvar *envp);

int			cmd_pwd(void);
char		*last_name(char *str);

int			ft_unset(char **a, t_msvar *msvar);

// // en_utils.c
int			env_add(const char *value, t_env *env);
char		*get_env_name(char *dest, const char *src);
int			is_in_env(t_env *env, char *args);
int			update_pwd(t_env *env);

// // shlvl.c
void		increment_shell_level(t_env *env);

// // env.c
size_t		size_env(t_env *lst);
char		*env_to_str(t_env *lst);
int			env_init(t_msvar *msvar, char **env_array);
int			secret_env_init(t_msvar *msvar, char **env_array);
void		free_env(t_env *env);

// // get_env.c
int			is_env_char(int c);
int			is_valid_env(const char *env);
int			env_value_len(const char *env);
char		*env_value(char *env);
char		*get_env_value(char *arg, t_env *env);

// // print_env.c
int			str_env_len(char **env);
void		sort_env(char **tabl, int env_len);
void		print_sorted_env(t_env *env);

// env_analzye.c fonction using the original envp to find data
// and initialisation
void		update_msenv(t_msvar *envp);
t_msvar		*ini_ms(char **envp);
char		**path_finder(char **envp);
void 		update_msenv(t_msvar *envp);

t_varchar	*dollar_data(char *str, int i, t_msvar *env);

// cpy_text.c
void		cpy_text_between_space(t_varchar *src, t_msvar *env);
void		add_dollar_data(t_varchar *src, t_msvar *env);
char		*ft_realloc(char *src, int diff);

// listmanip.c fonctions to manipulate a list
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstfirst(t_list *lst);
void		ft_lstadd_back(t_list *firstcmd, t_list *new);
t_list		*ft_ininewlst_el(void);

// ft_del.c fonctions used to delete stuff
void		del_el(char *el);
void		del_tab(char **el);
void		del_list(t_list *list_cmds);

// list_cmds.c create the chained list of cmds from the cmd line
t_list		*list_cmds(char *cmdline, t_msvar *ms_env);

// ft_pipe_split.c first op split the cmd line if there is pipes
int			ft_pipe_split(char *cmdline, t_list *cmd, int i);

// ft_in_out_files.c check the infile and outfile and fill them in the list
int			fill_inout(t_list *cmd, t_msvar *ms_env, int i, char c);
int			ft_check_in_out(t_list *cmd, t_msvar *ms_env);
int			ft_in_out_files(t_list *cmds, t_msvar *ms_env);

// ft_in_out_files2.c check the infile and outfile and fill them in the list
size_t		infile_size(char *cmdline, int i);
size_t		outfile_size(char *cmdline, int i);
int			inoutfileflag_ini(t_list *cmd, int i, char c);
int			ft_fill_infile(t_list *cmd, t_msvar *env, int i);
int			ft_fill_outfile(t_list *cmd, t_msvar *env, int i);

// ft_in_out_files3.c check the infile and outfile
int			pass_infile(char *src, int i);
int			pass_outfile(char *src, int i);
int			check_file_in(t_list *cmd, int fd_in);
int			check_file_out(t_list *cmd, int fd_out);

// quotes_utiles.c
int			quotesize(char *s, int i, char quotetype);
int			quotesize_incl(char *s, int i, char quotetype);
void		cpy_text_wquote(t_varchar *cpytext);
void		cpy_text_noquote(t_varchar *cpytext, t_msvar *env);
t_varchar	*fillvarchar(char *str, char *str2, int i, int j);

// ft_fill_data1.c et ft_fill_data2.c filling of the different data of
// chained list of commands
void		ft_clean_cmdline(t_list *cmd);
int			no_space(char *src, int i);
char		*cmd_path(char **path, char *cmd);
int			ft_fillpath_cmd(t_list *cmds, t_msvar *ms_env);
void		ft_fillcmd_flag(t_list *cmds, t_msvar *env);

// ft_splitcmd1.c and ft_splitcmd2.c used to split the string
// with the complete commande in a table
int			cntcmdline(char *s);
int			cntchar(char *s, char c, int i);
int			cntchar_noquote(char *s, char c, int i);
char		*cpycmdflag(t_varchar *listcmd, t_msvar *env);
char		**filltab(char *s, int nbline, t_msvar *env);
char		**ft_splitcmd(char *s, t_msvar *ms_env);

// pipe_children_process.c execute the commande
int			ft_heredoc(t_list *cmd);
int			checkbuiltin(char *cmd);
int			execbuiltin(t_list *cmds, int builtincmd_nb, t_msvar *ms_env);
int			one_cmd(t_list *list_cmds, t_msvar *ms_env, int *fd, int pid);

// ft_error_exit.c list of the insid errors and their number
// exit of minishell
int			ft_cmd_error(t_list *list_cmds, int error_type, t_msvar *ms_env);
int			ft_exit_minishell(t_msvar *ms_env);

// ft_pipe_spit.c
int			ft_pipe_split(char *cmdline, t_list *cmd, int i);

// pipe_utils.c
// int	in_out_fd(t_list *list_cmds, t_msvar *ms_env, int *fd, int *startfd);
int			in_out_fd(t_list *list_cmds, int *fd);
int			pipex(t_list *list_cmds, t_msvar *ms_env);
int			ft_pipe(char *cmdline, t_msvar *ms_env);

#endif
