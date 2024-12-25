/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:49:58 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 01:24:46 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	print_tokens(t_list *list)
{
	t_token	*t;

	while (list)
	{
		t = list->content;
		ft_printf("Type: %d, %s\n", t->type, t->value);
		list = list->next;
	}
}

void	lst_add(t_list **lst, void *content)
{
	t_list	*e;

	e = ft_lstnew(content);
	ft_lstadd_back(lst, e);
}
