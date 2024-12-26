/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2024/12/26 16:04:19 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execute(t_list *tokens)
{
	t_token * 	t = tokens->content;
	if (t->type == TOKEN_WORD)
	{
		select_builtin(t->value, tokens->next);
	}
}