/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:39:23 by asene             #+#    #+#             */
/*   Updated: 2025/01/18 17:47:25 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	**ft_lst_to_array(t_list *lst)
{
	void	**array;
	size_t	i;

	array = ft_calloc(ft_lstsize(lst) + 1, sizeof(void *));
	if (!array)
		return (NULL);
	i = 0;
	while (lst)
	{
		array[i++] = lst->content;
		lst = lst->next;
	}
	return (array);
}
