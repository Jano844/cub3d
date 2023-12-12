/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:21:02 by slippert          #+#    #+#             */
/*   Updated: 2023/11/27 19:19:46 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	current_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0
		|| (len > needle_len && ft_strncmp(haystack, needle, len) == 0))
		return ((char *)haystack);
	while (len && *haystack)
	{
		current_len = needle_len;
		while (*haystack == *needle && len && current_len)
		{
			len--;
			current_len--;
			haystack++;
			needle++;
		}
		if (!current_len)
			return ((char *)(haystack -= needle_len));
		len = (len + (needle_len - current_len)) - 1;
		haystack -= needle_len - current_len;
		needle -= needle_len - current_len;
		haystack++;
	}
	return (NULL);
}

int	ft_strnstr_bool(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	current_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0
		|| (len > needle_len && ft_strncmp(haystack, needle, len) == 0))
		return (0);
	while (len && *haystack)
	{
		current_len = needle_len;
		while (*haystack == *needle && len && current_len)
		{
			len--;
			current_len--;
			haystack++;
			needle++;
		}
		if (!current_len)
			return (1);
		len = (len + (needle_len - current_len)) - 1;
		haystack -= needle_len - current_len;
		needle -= needle_len - current_len;
		haystack++;
	}
	return (0);
}
