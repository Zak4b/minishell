/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsebasti <rsebasti@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:16:10 by asene             #+#    #+#             */
/*   Updated: 2024/12/29 14:00:02 by rsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	src_len;

	src_len = ft_strlen(str);
	if (start >= src_len)
		len = 0;
	else if (len > src_len - start)
		len = src_len - start;
	return (ft_strndup(str + start, len));
}
