/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 11:32:40 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 11:51:08 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*b_src = (const unsigned char *)src;
	unsigned char		*a_dst;

	a_dst = (unsigned char *)dst;
	if (a_dst < b_src)
		while (len--)
			*a_dst++ = *b_src++;
	else if (a_dst > b_src)
	{
		a_dst += len;
		b_src += len;
		while (len--)
			*(--a_dst) = *(--b_src);
	}
	return (dst);
}
