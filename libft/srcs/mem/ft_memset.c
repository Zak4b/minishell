/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asene <asene@student.42perpignan.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:09:26 by asene             #+#    #+#             */
/*   Updated: 2024/12/25 19:33:04 by asene            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdint.h>

// fills n bytes of the memory area pointed to by s with the constant byte c
// return a pointer to the matching byte or NULL
void	*ft_memset(void *dest, int value, size_t n)
{
	uint8_t		*d;
	uint64_t	block_value;
	uint8_t		byte_value;

	d = (uint8_t *)dest;
	byte_value = (uint8_t)value;
	block_value = (uint64_t)byte_value;
	block_value |= block_value << 8;
	block_value |= block_value << 16;
	block_value |= block_value << 32;
	while (n >= 8)
	{
		*(uint64_t *)d = block_value;
		d += 8;
		n -= 8;
	}
	while (n-- > 0)
		*d++ = byte_value;
	return (dest);
}
