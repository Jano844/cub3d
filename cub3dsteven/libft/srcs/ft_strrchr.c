/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:14:10 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 15:07:09 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*last_occurrence;
	unsigned char	a_c;

	last_occurrence = NULL;
	a_c = (unsigned char) c;
	while (*s)
	{
		if (*s == a_c)
			last_occurrence = (char *)s;
		s++;
	}
	if (a_c == *s)
		return ((char *)s);
	return (last_occurrence);
}
