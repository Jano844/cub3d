/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:56:57 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 13:47:27 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned char		*a_dst;
	const unsigned char	*b_src = (const unsigned char *)src;
	size_t				src_length;
	size_t				dst_length;
	size_t				counted;

	a_dst = (unsigned char *)dst;
	counted = 0;
	src_length = ft_strlen(src);
	dst_length = ft_strlen(dst);
	if (dst_length < dstsize - 1 && dstsize > 0)
	{
		while (*a_dst)
			a_dst++;
		while (*b_src && dst_length + counted < dstsize - 1)
		{
			*a_dst++ = *b_src++;
			counted++;
		}
		*a_dst = '\0';
	}
	if (dst_length >= dstsize)
		dst_length = dstsize;
	return (dst_length + src_length);
}
