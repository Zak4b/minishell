/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 15:56:53 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 11:54:46 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*list_to_string(t_list *lst)
{
	int		i;
	int		size;
	char	**split;
	char	*res;

	size = ft_lstsize(lst);
	split = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (lst)
	{
		split[i++] = lst->content;
		lst = lst->next;
	}
	res = ft_strnjoin(split, size, " ");
	free_split(split);
	return (res);
}

char	*build_word(t_tokenlist **lst)
{
	char 		*res;
	t_list		*string_lst;
	t_tokenlist	*t;

	t = *lst;
	string_lst = NULL;
	while (t && (t->token.type == TOKEN_SPACE || t->token.type == TOKEN_WORD))
	{
		ft_lstadd_back(&string_lst, ft_lstnew(ft_strdup(t->token.value)));
		t = t->next;
	}
	res = list_to_string(string_lst);
	ft_lstclear(&string_lst, free);
	return (res);
}

void	execute(t_vars *vars)
{
	(void)vars;
	// vars->current_token = vars->token_list;

	// if (vars->current_token->token.type == TOKEN_WORD)
	// {
	// 	select_builtin(t->value, tokens->next);
	// }
}