/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:49:58 by asene             #+#    #+#             */
/*   Updated: 2024/12/30 16:34:11 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strdoublejoin(char const *s1, char const *s2, char const *s3)
{
	char	*data[3];

	data[0] = (char *)s1;
	data[1] = (char *)s2;
	data[2] = (char *)s3;
	return (ft_strnjoin(data, 3, ""));
}

int	count_line(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	**list_to_array(t_list *lst)
{
	int		i;
	int		size;
	void	**array;

	size = ft_lstsize(lst);
	array = ft_calloc(size + 1, sizeof(void *));
	i = 0;
	while (lst)
	{
		array[i++] = lst->content;
		lst = lst->next;
	}
	return (array);
}

int	skip_spaces(char **str)
{
	if (!ft_isspace(**str))
		return (0);
	while (**str && ft_isspace(**str))
		(*str)++;
	return (1);
}
