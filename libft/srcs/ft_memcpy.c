/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:01:45 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 14:34:36 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*a_dst;
	const unsigned char	*b_src = (const unsigned char *)src;

	if (dst == NULL && src == NULL)
		return (NULL);
	a_dst = (unsigned char *)dst;
	while (n--)
		*a_dst++ = *b_src++;
	return (dst);
}
