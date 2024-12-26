/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:09:22 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 19:33:04 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>

// copies n bytes from memory area src to memory area dest. The memory areas may
// overlap: copying takes place as though the bytes in src are first copied into
// a temporary  array  that  does not overlap src or dest, and the bytes are
// then copied from the temporary array to dest. returns a pointer to dest.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	uint8_t	*d;
	uint8_t	*s;

	if (dest == src)
		return (dest);
	if (dest <= src)
		return (ft_memcpy(dest, src, n));
	d = (uint8_t *)dest + n;
	s = (uint8_t *)src + n;
	while (n >= 8)
	{
		d -= 8;
		s -= 8;
		*(uint64_t *)d = *(const uint64_t *)s;
		n -= 8;
	}
	while (n-- > 0)
		*--d = *--s;
	return (dest);
}
