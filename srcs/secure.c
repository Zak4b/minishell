/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:26:31 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/21 15:56:45 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirection(t_token t)
{
	if (t.type == TOKEN_REDIRECT_IN
		|| t.type == TOKEN_HEREDOC
		|| t.type == TOKEN_REDIRECT_OUT
		|| t.type == TOKEN_APPEND)
		return (true);
	return (false);
}

char	*token_str(t_token t)
{
	if (t.type == TOKEN_WORD)
		return (t.value);
	else if (t.type == TOKEN_PIPE)
		return ("|");
	else if (t.type == TOKEN_REDIRECT_IN)
		return ("<");
	else if (t.type == TOKEN_HEREDOC)
		return ("<<");
	else if (t.type == TOKEN_REDIRECT_OUT)
		return (">");
	else if (t.type == TOKEN_APPEND)
		return (">>");
	return (NULL);
}

t_token	next_token(t_tokenlist *tok_list)
{
	t_token	token;

	tok_list = tok_list->next;
	while (tok_list)
	{
		token = tok_list->token;
		if (token.type != TOKEN_SPACE)
			return (token);
		tok_list = tok_list->next;
	}
	return (token);
}

int	check(t_tokenlist *tok_list)
{
	if (tok_list->token.type == TOKEN_PIPE)
		return (ft_fprintf(2,
				"minishell: syntax error near unexpected token `|'\n"), 0);
	while (tok_list)
	{
		if ((is_redirection(tok_list->token)
				&& (next_token(tok_list).type == TOKEN_END
					|| next_token(tok_list).type == TOKEN_PIPE
					|| is_redirection(next_token(tok_list))))
			|| (tok_list->token.type == TOKEN_PIPE
				&& (next_token(tok_list).type == TOKEN_END
					|| next_token(tok_list).type == TOKEN_PIPE)))
		{
			if (next_token(tok_list).type != TOKEN_END)
				return (ft_fprintf(2,
						"minishell: syntax error near unexpected token `%s'\n",
						token_str(next_token(tok_list))), 0);
			return (ft_fprintf(2,
					"minishell: syntax error near unexpected token `newline'\n")
				, 0);
		}
		tok_list = tok_list->next;
	}
	return (1);
}
