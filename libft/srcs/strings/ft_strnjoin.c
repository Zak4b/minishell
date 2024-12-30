/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:55:36 by asene             #+#    #+#             */
/*   Updated: 2024/12/30 15:56:41 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnjoin(char **strs, unsigned int size, char *sep)
{
	unsigned int	i;
	unsigned int	len;
	char			*result;

	i = 0;
	len = 1;
	while (i < size)
		len += ft_strlen(strs[i++]);
	if (size != 0)
		len += (size - 1) * ft_strlen(sep);
	result = ft_calloc(len, sizeof(char));
	i = 0;
	while (i < size)
	{
		if (i != 0)
			ft_strlcat(result, sep, len);
		ft_strlcat(result, strs[i++], len);
	}
	return (result);
}
