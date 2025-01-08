/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 20:43:23 by rsebasti          #+#    #+#             */
/*   Updated: 2025/01/05 17:18:30 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_alone(t_vars *vars)
{
	t_tokenlist	*curent;

	curent = vars->current_token;
	if (curent->token.type <= TOKEN_HEREDOC && curent->token.type >= TOKEN_PIPE)
	{
		if (curent && !curent->next)
		{
			if (curent->token.type != TOKEN_PIPE)
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n");
			else
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n");
		}
	}

}

int	syntax_checker(t_vars *vars)
{
	
}