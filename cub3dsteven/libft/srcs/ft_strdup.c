/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:20:04 by slippert          #+#    #+#             */
/*   Updated: 2023/10/14 10:37:26 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		i;
	int		len;
	char	*a;

	a = (char *) s1;
	i = 0;
	len = 0;
	while (a[len] != '\0')
		len++;
	s = (char *)malloc(len + 1);
	if (!s)
		return (NULL);
	while (a[i] != '\0')
	{
		s[i] = a[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
