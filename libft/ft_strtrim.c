/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:16:30 by asene             #+#    #+#             */
/*   Updated: 2024/11/08 14:04:38 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	int		i;

	while (*str && ft_strchr(set, *str))
		str++;
	i = ft_strlen(str) - 1;
	while (i > 0 && ft_strrchr(set, str[i]))
		i--;
	return (ft_substr(str, 0, i + 1));
}
