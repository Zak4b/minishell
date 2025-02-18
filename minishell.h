/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:52:55 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:48:18 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>

extern volatile sig_atomic_t	g_nal;

typedef enum e_exit_code
{
	SUCCESS = 0,
	FAILURE = 1,
	BAD_USAGE = 2,
	FILE_ERROR = 126,
	NOT_FOUND = 127,
	MAX_EXIT_CODE = 255
}	t_exit_code;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SPACE,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_exec_data
{
	char				*path;
	char				**args;
	int					argc;
	int					fd_in;
	int					fd_out;
	struct s_exec_data	*prev;
	struct s_exec_data	*pipe;
}	t_exec;

typedef struct s_vars
{
	t_list				*env;
	t_token				*token_list;
	t_exec				*exec_data;
	int					exit_code;
	int					nbheredoc;
	void				*tmp;
	struct sigaction	sa;
}	t_vars;

char		*readline_prompt(t_vars *vars, char **dest);

void		clean_exit(t_vars *vars, int exit_code);
int			count_line(char **str);
char		*str_append(char **dest, char *next);

t_token		*tokenize(char *input);
void		token_append(t_token **lst, t_token_type type, char *value);
void		clear_token_list(t_token **t);

char		*eval_string(t_vars *vars, char *str, bool *has_quote);
char		*replace_vars(t_vars *vars, char *str);

char		*search_path(t_vars *vars, char *cmd);

void		parse_env(char **env, t_vars *vars);
char		*getenv_value(t_vars *vars, char *key);
char		*get_var_string(t_vars *vars, char *var_name);
char		**build_env(t_vars *vars);
void		set_env(t_vars *vars, char *key, char *value);
void		unset_env(t_vars *vars, char *key);

t_exec		*build_exec(t_vars *vars, t_token *tok_lst,
				t_exec **data, t_exec *prev);
void		free_exec(t_exec *data);

bool		is_builtin(char *cmd);
int			exec_builtin(t_vars *vars, t_exec *data);
int			execute(t_vars *vars);
int			run_cmd(t_vars *vars, t_exec *data, bool need_fork);
int			execute_pipeline(t_vars *vars, t_exec *data, int input_fd);

int			ft_cd(t_vars *vars, t_exec *data);
int			ft_export(t_vars *vars, t_exec *data);
int			ft_pwd(t_vars *vars, t_exec *data);
int			ft_echo(t_vars *vars, t_exec *data);
int			ft_exit(t_vars *vars, t_exec *data);
int			ft_env(t_vars *vars, t_exec *data);
int			ft_unset(t_vars *vars, t_exec *data);

int			start_signal(t_vars *vars);
int			stop_signal(t_vars *vars);
int			heredoc(t_vars *vars, char *delimiter, bool eval_vars);
void		heredoc_killer(int nbheredoc);
bool		check(t_token *tok_list);
bool		is_redirection(t_token t);
bool		is_limit_token(t_token t);
char		*token_str(t_token *t);
int			exec_error(t_vars *vars, t_exec *data);

void		file_error(char *file);
void		syntaxe_error(t_token *token);
void		catch_sign(int sign);
void		handle_heredoc(int sig);

#endif