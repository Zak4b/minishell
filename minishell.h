/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:52:55 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 13:32:57 by rsebasti         ###   ########.fr       */
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

typedef struct s_var
{
	char 	**env;
	char 	**builtins;
	int		envsize;
	
} t_var;


t_list		*tokenize(const char *input);
void		free_token(t_token *t);

int			is_space(char c);
void		lst_add(t_list **lst, void *content);

char		*search_path(char **env, char *cmd);
char		*ft_strdoublejoin(char const *s1, char const *s2, char const *s3);
t_word_type	cmd_or_file(char *token, char **env);
int			setup_sign(void);

void		select_builtin(char *builtin, t_list *tokens, t_var *vars);
void		execute(t_list *tokens, t_var *vars);

int			count_line(char **str);
void		env_parser(char **env, t_var *vars);

#endif