/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:02:41 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 19:19:23 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	a_c;

	a_c = (unsigned char) c;
	while (*s)
	{
		if (*s == a_c)
			return ((char *)s);
		s++;
	}
	if (a_c == *s)
		return ((char *)s);
	return (NULL);
}
