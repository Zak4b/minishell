/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:02:49 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 19:33:04 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*dup;

	dup = malloc(sizeof(char) * (n + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
