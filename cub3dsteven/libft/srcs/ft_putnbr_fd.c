/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:09:40 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 09:40:32 by slippert         ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	char	str[32];
	size_t	size;
	size_t	is_neg;
	long	nn;

	is_neg = 0;
	nn = (long)n;
	size = get_chars(nn);
	str[size] = '\0';
	if (nn < 0)
	{
		nn = -nn;
		is_neg = 1;
	}
	while (size > is_neg)
	{
		str[--size] = nn % 10 + '0';
		nn /= 10;
	}
	if (is_neg)
		str[--size] = '-';
	ft_putstr_fd(str, fd);
}
