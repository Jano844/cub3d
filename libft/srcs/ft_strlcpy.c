/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:20:07 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 13:57:16 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t
	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char		*a_dst;
	const unsigned char	*b_src = (const unsigned char *)src;
	size_t				cmb_length;

	cmb_length = 0;
	a_dst = (unsigned char *)dst;
	if (dstsize)
	{
		while (*b_src && cmb_length < (dstsize - 1))
		{
			cmb_length++;
			*a_dst++ = *b_src++;
		}
		*a_dst = '\0';
	}
	while (*b_src++)
		cmb_length++;
	return (cmb_length);
}
