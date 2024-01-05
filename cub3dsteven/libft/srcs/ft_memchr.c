/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:47:21 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 15:29:29 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*a_s = (const unsigned char *)s;
	unsigned char			uc;

	uc = (unsigned char)c;
	while (n--)
	{
		if (*a_s == uc)
			return ((void *)a_s);
		a_s++;
	}
	return ((void *)0);
}
