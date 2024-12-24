/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:09:22 by asene             #+#    #+#             */
/*   Updated: 2024/11/08 13:35:46 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copies n bytes from memory area src to memory area dest. The memory areas may
// overlap: copying takes place as though the bytes in src are first copied into
// a temporary  array  that  does not overlap src or dest, and the bytes are
// then copied from the temporary array to dest. returns a pointer to dest.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*p_dest;
	unsigned char	*p_src;

	if (dest == src)
		return (dest);
	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (dest <= src)
		ft_memcpy(dest, src, n);
	else
	{
		i = n;
		while (i-- > 0)
			p_dest[i] = p_src[i];
	}
	return (dest);
}
