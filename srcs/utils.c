/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:49:58 by asene             #+#    #+#             */
/*   Updated: 2025/01/09 14:22:40 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*str_append(char **dest, char *next)
{
	unsigned int	new_len;
	char			*new_str;

	new_len = ft_strlen(*dest) + ft_strlen(next) + 1;
	new_str = ft_calloc(new_len, sizeof(char));
	ft_strlcat(new_str, *dest, new_len);
	ft_strlcat(new_str, next, new_len);
	free(*dest);
	*dest = new_str;
	return (new_str);
}
