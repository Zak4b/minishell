/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:49:58 by asene             #+#    #+#             */
/*   Updated: 2024/12/27 15:24:01 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*ft_strdoublejoin(char const *s1, char const *s2, char const *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

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
