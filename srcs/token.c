/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:46:54 by asene             #+#    #+#             */
/*   Updated: 2024/12/30 16:10:17 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_append(t_tokenlist **lst, t_token_type type, char *value)
{
	t_tokenlist	*e;
	t_tokenlist	*last;

	e = ft_calloc(1, sizeof(t_tokenlist));
	e->next = NULL;
	e->token.type = type;
	e->token.value = value;
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
		if (!quote && (ft_isspace((*p)[i]) || ft_strchr("|<>\"'", (*p)[i])))
			break ;
		i++;
	}
	return (res = ft_substr(*p, 0, i), *p += i, res);
}

void	get_next_token(t_tokenlist **list, char **input)
{
	if (**input == '|' && ++(*input))
		token_append(list, TOKEN_PIPE, ft_strdup("|"));
	else if (**input == '>' && ++(*input))
	{
		if (**input == '>' && ++(*input))
			token_append(list, TOKEN_APPEND, ft_strdup(">>"));
		else
			token_append(list, TOKEN_REDIRECT_OUT, ft_strdup(">"));
	}
	else if (**input == '<' && ++(*input))
	{
		if (**input == '<' && ++(*input))
			token_append(list, TOKEN_HEREDOC, ft_strdup("<<"));
		else
			token_append(list, TOKEN_REDIRECT_IN, ft_strdup("<"));
	}
	else if (**input)
		token_append(list, TOKEN_WORD, grab_word(input));
}

t_tokenlist	*tokenize(const char *input)
{
	t_tokenlist	*list;

	list = NULL;
	while (*input)
	{
		if (*input && ft_isspace(*input))
		{
			while (*input && ft_isspace(*input))
				input++;
			token_append(&list, TOKEN_SPACE, ft_strdup(" "));
		}
		get_next_token(&list, (char **)&input);
	}
	return (token_append(&list, TOKEN_END, NULL), list);
}

void	clear_token_list(t_tokenlist **t)
{
	t_tokenlist	*next;

	while (t && *t)
	{
		next = (*t)->next;
		if ((*t)->token.value)
		{
			free((*t)->token.value);
			(*t)->token.value = NULL;
		}
		free(*t);
		*t = next;
	}
}
