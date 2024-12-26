/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 20:52:55 by asene             #+#    #+#             */
/*   Updated: 2024/12/26 11:16:25 by asene            ###   ########.fr       */
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

t_list		*tokenize(const char *input);
void		free_token(t_token *t);

int			is_space(char c);
void		lst_add(t_list **lst, void *content);

char		*search_path(char **env, char *cmd);
char		*ft_strdoublejoin(char const *s1, char const *s2, char const *s3);
t_word_type	cmd_or_file(char *token, char **env);
int			setup_sign(void);

#endif