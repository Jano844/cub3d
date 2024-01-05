/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:24:00 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 09:40:14 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_chars(long n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (++count);
	if (n < 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_process(char *str, size_t counted, size_t is_neg, long nn)
{
	if (counted == 0)
	{
		str[0] = '0';
	}
	if (nn < 0)
	{
		is_neg = 1;
		nn = -nn;
	}
	while (counted > is_neg)
	{
		str[--counted] = nn % 10 + '0';
		nn /= 10;
	}
	if (counted)
		str[--counted] = '-';
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	counted;
	size_t	is_neg;
	long	nn;

	nn = (long)n;
	is_neg = 0;
	counted = get_chars(nn);
	str = ft_calloc(counted + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_process(str, counted, is_neg, nn);
	return (str);
}
