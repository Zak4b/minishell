/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:11:59 by asene             #+#    #+#             */
/*   Updated: 2024/12/26 13:37:36 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*content;
	t_list	*new_list;
	t_list	*new_item;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		new_item = ft_lstnew(content);
		if (new_item == NULL)
			return (ft_lstclear(&new_list, del), free(content), NULL);
		ft_lstadd_back(&new_list, new_item);
		lst = lst->next;
	}
	return (new_list);
}
