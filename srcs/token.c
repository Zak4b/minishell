/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:46:54 by asene             #+#    #+#             */
/*   Updated: 2025/01/22 23:07:41 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_append(t_token **lst, t_token_type type, char *value)
{
	t_token	*e;
	t_token	*last;

	e = ft_calloc(1, sizeof(t_token));
	e->next = NULL;
	e->type = type;
	e->value = value;
	if (*lst == NULL)
		return (*lst = e, (void)0);
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = e;
}

char	*grab_word(char **p)
{
	int		i;
	char	quote;
	char	*res;

	i = 0;
	quote = 0;
	if (ft_strchr("'\"", **p))
		quote = **p + i++;
	while ((*p)[i])
	{
		if (quote && (*p)[i] == quote && ++i)
			break ;
		if (!quote && (ft_strchr(" \t\n\v\f\r;|<>\"'", (*p)[i])
			|| !ft_strncmp(&(*p)[i], "&&", 2)))
			break ;
		i++;
	}
	return (res = ft_substr(*p, 0, i), *p += i, res);
}

void	get_next_token(t_token **list, char **input)
{
	t_token_type	type;

	type = TOKEN_WORD;
	if (**input == ';' && ++(*input))
		type = TOKEN_END;
	else if (!ft_strncmp(*input, "&&", 2) && ++(*input) && ++(*input))
		type = TOKEN_AND;
	else if (!ft_strncmp(*input, "||", 2) && ++(*input) && ++(*input))
		type = TOKEN_OR;
	else if (**input == '|' && ++(*input))
		type = TOKEN_PIPE;
	else if (!ft_strncmp(*input, ">>", 2) && ++(*input) && ++(*input))
		type = TOKEN_APPEND;
	else if (**input == '>' && ++(*input))
		type = TOKEN_REDIRECT_OUT;
	else if (!ft_strncmp(*input, "<<", 2) && ++(*input) && ++(*input))
		type = TOKEN_HEREDOC;
	else if (**input == '<' && ++(*input))
		type = TOKEN_REDIRECT_IN;
	if (type != TOKEN_WORD)
		skip_spaces(input);
	if (type == TOKEN_WORD)
		token_append(list, type, grab_word(input));
	else
		token_append(list, type, NULL);
}

t_token	*tokenize(char *input)
{
	t_token	*list;

	list = NULL;
	while (*input)
	{
		if (skip_spaces(&input))
			token_append(&list, TOKEN_SPACE, NULL);
		if (*input)
			get_next_token(&list, (char **)&input);
	}
	return (list);
}

void	clear_token_list(t_token **t)
{
	t_token	*next;

	while (t && *t)
	{
		next = (*t)->next;
		if ((*t)->value)
		{
			free((*t)->value);
			(*t)->value = NULL;
		}
		free(*t);
		*t = next;
	}
}
