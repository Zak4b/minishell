/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:26:31 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/16 15:52:15 by asene            ###   ########.fr       */
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

bool	check_syntax(t_tokenlist *tok_lst)
{
	while (tok_lst)
	{
		if (is_redirection(tok_lst->token))
			if (ft_strlen(tok_lst->token.value) == 0)
				return (false);
		//else if ()

		tok_lst = tok_lst->next;
	}
	return (true);
}

int	check(t_tokenlist *tok_list)
{
	if (tok_list->token.type == TOKEN_PIPE)
		return (ft_fprintf(2,
				"minishell: syntax error near unexpected token `|'\n"), 0);
	while (tok_list)
	{
		if (tok_list->token.type >= TOKEN_REDIRECT_IN
			&& tok_list->token.type <= TOKEN_HEREDOC
			&& ft_strlen(tok_list->token.value) == 0)
		{
			if (tok_list->next->token.type != TOKEN_END)
				return (ft_fprintf(2,
						"mini: syntax error near unexpected token `%s'\n",
						token_str(tok_list->token)), 0);
			return (ft_fprintf(2,
					"minishell: syntax error near unexpected token `newline'\n")
				, 0);
		}
		tok_list = tok_list->next;
	}
	return (1);
}
