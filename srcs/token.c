/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:46:54 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 20:15:46 by rsebasti         ###   ########.fr       */
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

t_list	*tokenize(const char *input)
{
	t_list		*list;
	const char	*ptr;

	ptr = input;
	list = NULL;
	while (*ptr)
	{
		while (*ptr && is_space(*ptr))
			ptr++;
		if (*ptr == '|' && ++ptr)
			lst_add(&list, new_token(TOKEN_PIPE, ft_strdup("|")));
		else if (*ptr == '>')
		{
			if (*(ptr + 1) == '>' && ++ptr)
				lst_add(&list, new_token(TOKEN_APPEND, ft_strdup(">>")));
			else
				lst_add(&list, new_token(TOKEN_REDIRECT_OUT, ft_strdup(">")));
			ptr++;
		}
		else if (*ptr == '<' && ++ptr)
			lst_add(&list, new_token(TOKEN_REDIRECT_IN, ft_strdup("<")));
		else
			lst_add(&list, new_token(TOKEN_WORD, get_token((char **)&ptr)));
	}
	return (lst_add(&list, new_token(TOKEN_END, NULL)), list);
}

void	free_token(t_token *t)
{
	if (t->value != NULL)
		free(t->value);
	free(t);
}
