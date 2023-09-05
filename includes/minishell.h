/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qroussea <qroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:43:42 by qroussea          #+#    #+#             */
/*   Updated: 2022/05/16 16:28:10 by qroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <sys/param.h>
# include "../libft/libft.h"

# define GREY		"\1\x1b[30m\2"
# define RED		"\1\x1b[31m\2"
# define GREEN		"\1\x1b[32m\2"
# define YELLOW		"\1\x1b[33m\2"
# define BLUE		"\1\x1b[34m\2"
# define PURPLE		"\1\x1b[35m\2"
# define CYAN		"\1\x1b[36m\2"
# define WHITE		"\1\x1b[37m\2"
# define END		"\1\x1b[0m\2"
# define BOLD		"\1\x1b[1m\2"
# define UNDER		"\1\x1b[4m\2"
# define REV		"\1\x1b[7m\2"

typedef int	t_bool;

int			g_return_value;

typedef struct s_fd
{
	int		infile;
	int		outfile;
}	t_fd;

typedef struct s_cmddata
{
	int		infile;
	int		outfile;
	char	**cmd;
	int		sep;
	int		nextsep;
	int		status;
	t_bool	enterbrack;
	t_bool	exitbrack;
}	t_cmddata;

typedef struct s_shell
{
	char		**env;
	int			nextincmd;
	t_cmddata	*cmd;
	t_bool		last_cmd;
	int			inbrack;
	int			count;
	t_bool		checking;
	t_bool		pass;
}	t_shell;

/******************************************************************************/

void		rl_replace_line(const char *str, int d);
t_cmddata	*parsing(char	*line, t_shell *shell);

/*************************** HANDLER FUNCTIONS ********************************/

void		redirect_handler(char *handler, int sig);

/************************** EXECUTION FUNCTIONS *******************************/

int			execution(t_shell *shell);
char		*search_cmd_path(t_shell *shell, char *cmd);
int			struct_initialisation(t_shell *shell, char **envp, int c, void *v);
void		close_fd(int *fd);
void		child_fd_redirect(t_shell *shell, int *fd);
int			check_pid(t_shell *shell, pid_t	pid, int *fd);

/************************* ENVIRONMENT FUNCTIONS ******************************/

char		**create_env(char **envp);
int			index_search_in_env(char **env, char *name);
char		*search_in_env(char **env, char *name);
void		env_add(t_shell *shell, char *str);
void		replace_env(t_shell *shell, char *search, char *replace);
void		env(t_shell *shell);
// void		env_add(char ***env, char *str);
// void			replace_env(char **env, char *search, char *replace);

/*************************** BUILTIN FUNCTIONS ********************************/

int			check_builtin(char **cmd);
void		exec_builtin(t_shell *shell, char **cmd);
void		exit_builtin(char *cmd, char *arg, char *error, int exit_value);
void		pwd(void);
void		cd(t_shell *shell, char *dir);
void		unset(t_shell *shell, char **search);
char		**initialized_export(t_shell *shell);
void		export(t_shell *shell, char **ptr);
void		echo(char **arg);
void		shell_exit(char **ptr);

/************************ PARSING WORD FUNCTIONS ******************************/

int			get_env_var(char	**line, int *buff, t_shell *shell, int i);
int			ft_getword(t_cmddata *res, char	**line,
				char **word, t_shell *shell);

/************************ PARSING UTILS FUNCTIONS *****************************/

int			is_backslash(char *pos);
int			ft_issep(char	*totest);
char		*ft_strdelchar(char *str, char c);
int			ft_heredoc(char	*limiter, t_shell *shell);
int			ft_openfile(char *file, int fd, t_bool append, int *lastfd);
int			ft_istoken(char *word);
void		*ft_perror(char *str);
int			preparsing(char	*line, t_shell	*shell, t_cmddata	*result);
void		pass_space_and(t_cmddata	*res, char **line, int n);

/************************ PARSING CALCUL FUNCTIONS ****************************/

int			ft_cmdnb(char	*line);
int			ft_cmdlenght(char	*line);
int			ft_wildcardcmp(char *s1, char *s2);
int			ft_wildcard(t_cmddata	*res, char	*word);
int			ft_addtocmd(t_cmddata	*res, char	*toadd);

/******************************************************************************/

#endif
