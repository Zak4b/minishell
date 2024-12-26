/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:12:50 by asene             #+#    #+#             */
/*   Updated: 2024/12/26 13:31:48 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "stdint.h"

void	*ft_calloc(size_t count, size_t element_size)
{
	void	*ptr;
	size_t	total_size;

	total_size = count * element_size;
	if (total_size && SIZE_MAX / element_size < count)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr != NULL)
		ft_bzero(ptr, total_size);
	return (ptr);
}
