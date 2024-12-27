/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:46:54 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 13:53:07 by asene            ###   ########.fr       */
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

char	*get_token(char **ptr)
{
	int		i;
	char	quote;
	char	*res;

	i = 0;
	quote = 0;
	if (ft_strchr("'\"", **ptr))
		quote = **ptr + i++;
	while ((*ptr)[i])
	{
		if (quote && (*ptr)[i] == quote && ++i)
			break ;
		if (!quote && (is_space((*ptr)[i]) || ft_strchr("|<>\"'", (*ptr)[i])))
			break ;
		i++;
	}
	return (res = ft_substr(*ptr, 0, i), *ptr += i, res);
}

void	add_token(t_tokenlist **list, char **input)
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
		token_append(list, TOKEN_WORD, get_token(input));
}

t_tokenlist	*tokenize(const char *input)
{
	t_tokenlist	*list;

	list = NULL;
	while (*input)
	{
		if (*input && is_space(*input))
		{
			while (*input && is_space(*input))
				input++;
			token_append(&list, TOKEN_SPACE, NULL);
		}
		add_token(&list, (char **)&input);
	}
	return (token_append(&list, TOKEN_END, NULL), list);
}

void	clear_token_list(t_tokenlist *t)
{
	t_tokenlist	*next;

	while (t)
	{
		next = t->next;
		free(t->token.value);
		t->token.value = NULL;
		free(t);
		t = NULL;
		t = next;
	}
	
}
