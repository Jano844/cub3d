/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 12:39:13 by slippert          #+#    #+#             */
/*   Updated: 2023/10/09 15:21:35 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (*s1 && *s2 && --n)
		{
			if (*s1 != *s2)
				break ;
			s1++;
			s2++;
		}
	}
	else
		return (0);
	return ((unsigned char) *s1 - (unsigned char) *s2);
}
