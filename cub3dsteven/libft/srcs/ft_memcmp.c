/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:10:36 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 11:50:12 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*a_s1 = (const unsigned char *)s1;
	const unsigned char	*b_s2 = (const unsigned char *)s2;

	while (n--)
	{
		if (*a_s1 != *b_s2)
			return (*a_s1 - *b_s2);
		a_s1++;
		b_s2++;
	}
	return (0);
}
