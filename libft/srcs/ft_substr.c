/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:35:33 by slippert          #+#    #+#             */
/*   Updated: 2023/11/25 14:16:39 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	char	*temp_sub_s;
	size_t	count;
	size_t	count_sub;
	size_t	size_s;

	size_s = ft_strlen(s);
	if (len > size_s)
		len = size_s;
	sub_s = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub_s)
		return (NULL);
	count_sub = 0;
	count = 0;
	temp_sub_s = sub_s;
	while (s[count] && count_sub < len)
	{
		if (count >= start)
		{
			*sub_s++ = s[count];
			count_sub++;
		}
		count++;
	}
	return (temp_sub_s);
}

char
	*ft_substr_free(char *s, unsigned int start, size_t len)
{
	char	*sub_s;
	char	*temp_sub_s;
	size_t	count;
	size_t	count_sub;
	size_t	size_s;

	size_s = ft_strlen(s);
	if (len > size_s)
		len = size_s;
	sub_s = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub_s)
		return (NULL);
	count_sub = 0;
	count = -1;
	temp_sub_s = sub_s;
	while (s[++count] && count_sub < len)
	{
		if (count >= start)
		{
			*sub_s++ = s[count];
			count_sub++;
		}
	}
	free(s);
	return (temp_sub_s);
}
