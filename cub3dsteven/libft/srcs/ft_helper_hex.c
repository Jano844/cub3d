/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:30:06 by slippert          #+#    #+#             */
/*   Updated: 2023/11/24 09:42:17 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexlen(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

// uintptr_t	quotient;
// quotient = num / 16;
uintptr_t	ft_calculate(uintptr_t num)
{
	uintptr_t	result;

	result = num % 16;
	return (result);
}

int	ft_calcptr(uintptr_t num, char x)
{
	uintptr_t	result;
	char		str[16];
	int			i;
	int			length;

	i = 0;
	while (num)
	{
		result = ft_calculate(num);
		num = num / 16;
		if (result <= 9)
			str[i++] = result + '0';
		else
		{
			if (x == 'x')
				str[i++] = result - 10 + 'a';
			else
				str[i++] = result - 10 + 'A';
		}
	}
	length = i;
	while (i--)
		if (ft_putchar(str[i]) == -1)
			return (-1);
	return (length);
}

int	ft_putptr(void *ptr)
{
	int	length;
	int	temp_len;

	if (!ptr)
		return (ft_putstr("0x0"));
	length = ft_putstr("0x");
	if (length == -1)
		return (length);
	if ((uintptr_t)ptr <= 9)
		temp_len = ft_putchar((uintptr_t)ptr + '0');
	else
		temp_len = ft_calcptr((uintptr_t)ptr, 'x');
	if (temp_len == -1)
		return (-1);
	length += temp_len;
	return (length);
}

int	ft_puthex(unsigned int n, char x)
{
	int	length;

	length = 0;
	if (!n)
		length = write(1, "0", 1);
	else
	{
		if (n <= 9)
			length += ft_putchar(n + '0');
		else
			length += ft_calcptr(n, x);
	}
	return (length);
}
