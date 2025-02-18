/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:15:30 by asene             #+#    #+#             */
/*   Updated: 2025/02/18 14:15:39 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token_list(t_token **t)
{
	t_token	*next;

	while (t && *t)
	{
		next = (*t)->next;
		if ((*t)->value)
		{
			free((*t)->value);
			(*t)->value = NULL;
		}
		free(*t);
		*t = next;
	}
}