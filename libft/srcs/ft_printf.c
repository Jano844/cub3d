/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:04:50 by slippert          #+#    #+#             */
/*   Updated: 2023/10/29 09:48:28 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formats(va_list args, const char format)
{
	int	length;

	length = -1;
	if (format == 'c')
		length = ft_putchar(va_arg(args, int));
	else if (format == 's')
		length = ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		length = ft_putptr(va_arg(args, void *));
	else if (format == 'i' || format == 'd')
		length = ft_putint(va_arg(args, int));
	else if (format == 'u')
		length = ft_putuint(va_arg(args, unsigned int));
	else if (format == 'x')
		length = ft_puthex(va_arg(args, unsigned int), 'x');
	else if (format == 'X')
		length = ft_puthex(va_arg(args, unsigned int), 'X');
	else if (format == '%')
		length = ft_putpercent();
	return (length);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;
	int		length;
	int		temp_len;

	i = 0;
	length = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			temp_len = ft_formats(args, format[i++ + 1]);
		else
			temp_len = ft_putchar(format[i]);
		if (temp_len == -1)
		{
			length = -1;
			break ;
		}
		length += temp_len;
		i++;
	}
	return (va_end(args), length);
}
