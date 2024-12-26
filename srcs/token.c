/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:46:54 by asene             #+#    #+#             */
/*   Updated: 2024/12/26 11:05:12 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*t;

	t = ft_calloc(1, sizeof(t_token));
	t->type = type;
	t->value = value;
	return (t);
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

void	add_token(t_list **list, char **input)
{
	if (**input == '|' && ++(*input))
		lst_add(list, new_token(TOKEN_PIPE, ft_strdup("|")));
	else if (**input == '>' && ++(*input))
	{
		if (**input == '>' && ++(*input))
			lst_add(list, new_token(TOKEN_APPEND, ft_strdup(">>")));
		else
			lst_add(list, new_token(TOKEN_REDIRECT_OUT, ft_strdup(">")));
	}
	else if (**input == '<' && ++(*input))
	{
		if (**input == '<' && ++(*input))
			lst_add(list, new_token(TOKEN_HEREDOC, ft_strdup("<<")));
		else
			lst_add(list, new_token(TOKEN_REDIRECT_IN, ft_strdup("<")));
	}
	else if (**input)
		lst_add(list, new_token(TOKEN_WORD, get_token(input)));
}

t_list	*tokenize(const char *input)
{
	t_list		*list;

	list = NULL;
	while (*input)
	{
		if (*input && is_space(*input))
		{
			while (*input && is_space(*input))
				input++;
			lst_add(&list, new_token(TOKEN_SPACE, NULL));
		}
		add_token(&list, (char **)&input);
	}
	return (lst_add(&list, new_token(TOKEN_END, NULL)), list);
}

void	free_token(t_token *t)
{
	if (t->value != NULL)
		free(t->value);
	free(t);
}
