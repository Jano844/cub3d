/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 09:57:04 by slippert          #+#    #+#             */
/*   Updated: 2023/10/24 10:52:38 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **split, size_t words)
{
	while (words > 0)
	{
		if (split[words - 1])
			free(split[words - 1]);
		words--;
	}
	free(split);
}

static size_t	get_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	ft_progress(char const *s, char c, char **split, size_t words)
{
	size_t	word_len;
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (s[count] && i < words)
	{
		word_len = 0;
		while (s[count] == c && s[count])
			count++;
		while (s[count] != c && s[count])
		{
			count++;
			word_len++;
		}
		if (word_len > 0)
			split[i] = ft_substr(s, count - word_len, word_len);
		if (split[i] == NULL)
			ft_free(split, words);
		i++;
	}
	split[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words;

	if (!s)
		return (NULL);
	words = get_words(s, c);
	split = ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (NULL);
	ft_progress(s, c, split, words);
	return (split);
}
