/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:26:31 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/21 22:48:47 by asene            ###   ########.fr       */
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

bool	is_limit_token(t_token t)
{
	if (t.type == TOKEN_PIPE
		|| t.type == TOKEN_END)
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

int	check(t_token *tok_list)
{
	if (tok_list->type == TOKEN_PIPE)
		return (ft_fprintf(2,
				"minishell: syntax error near unexpected token `|'\n"), 0);
	while (tok_list)
	{
		if ((is_redirection(*tok_list)
				&& tok_list->type != TOKEN_SPACE
				&& ft_strlen(tok_list->value) == 0)
			|| (tok_list->type == TOKEN_PIPE
				&& (next_token(tok_list)->type == TOKEN_END
					|| next_token(tok_list)->type == TOKEN_PIPE)))
		{
			if (tok_list->next->type != TOKEN_END)
				return (ft_fprintf(2,
						"minishell: syntax error near unexpected token `%s'\n",
						token_str(*tok_list)), 0);
			return (ft_fprintf(2,
					"minishell: syntax error near unexpected token `newline'\n")
				, 0);
		}
		tok_list = tok_list->next;
	}
	return (1);
}
