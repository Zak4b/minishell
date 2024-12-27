/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:52:55 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 19:29:42 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>

extern int	g_nal;

typedef enum e_word_type
{
	W_NONE,
	W_BUILTIN,
	W_EXECUTABLE,
	W_FILE,
	W_CMD
}	t_word_type;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_SPACE,
	TOKEN_VAR,
	TOKEN_END
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_tokenlist
{
	t_token				token;
	struct s_tokenlist	*next;
}	t_tokenlist;

typedef struct s_exec_data
{
	char	*path;
	char	**args;
}	t_exec_data;

typedef struct s_vars
{
	char		**env;
	char		**builtins;
	int			envsize;
	t_tokenlist	*token_list;
	t_tokenlist	*current_token;
}	t_vars;

t_tokenlist	*tokenize(const char *input);
void		token_append(t_tokenlist **lst, t_token_type type, char *value);
void		clear_token_list(t_tokenlist **t);

int			is_space(char c);

char		*search_path(char **env, char *cmd);
char		*clean_word(char **env, char *word);
char		*ft_strdoublejoin(char const *s1, char const *s2, char const *s3);
char		*ft_strnjoin(char **strs, unsigned int size, char *sep);
t_word_type	cmd_or_file(char *token, char **env);
int			setup_sign(void);

void		exec_builtin(t_vars *vars);
int			count_line(char **str);
void		env_parser(char **env, t_vars *vars);
void		execute(t_vars *vars);

#endif