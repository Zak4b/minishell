/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:26:31 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/27 13:50:44 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_token(t_token *tok_list)
{
	tok_list = tok_list->next;
	while (tok_list)
	{
		if (tok_list->type != TOKEN_SPACE)
			return (tok_list);
		tok_list = tok_list->next;
	}
	return (tok_list);
}

bool	check_open_quote(t_token *token)
{
	size_t	len;

	len = ft_strlen(token->value);
	if (ft_strchr("'\"", token->value[0]))
	{
		if (token->value[len - 1] != token->value[0])
			return (false);
	}
	return (true);
}

bool	check(t_token *tok_list)
{
	t_token	*next;

	if (!tok_list)
		return (true);
	else if (is_limit_token(*tok_list) && tok_list->type != TOKEN_END)
		return (syntaxe_error(tok_list), false);
	while (tok_list)
	{
		next = next_token(tok_list);
		if ((is_redirection(*tok_list) && (!next || next->type != TOKEN_WORD))
			|| (is_limit_token(*tok_list)
				&& (!next || is_limit_token(*next))))
			return (syntaxe_error(next), false);
		if (next == NULL)
			break ;
		tok_list = next;
	}
	if (tok_list->type == TOKEN_WORD && !check_open_quote(tok_list))
		return (syntaxe_error(tok_list), false);
	return (true);
}
