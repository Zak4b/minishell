/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:09:15 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 19:33:04 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>

// copies n bytes from memory area src to memory area dest.  The memory areas
// must not overlap. returns a pointer to dest.
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	uint8_t	*d;
	uint8_t	*s;

	d = (uint8_t *)dest;
	s = (uint8_t *)src;
	while (n >= 8)
	{
		*(uint64_t *)d = *(const uint64_t *)s;
		d += 8;
		s += 8;
		n -= 8;
	}
	while (n-- > 0)
		*d++ = *s++;
	return (dest);
}
