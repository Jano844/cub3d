/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper_csi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:56:47 by slippert          #+#    #+#             */
/*   Updated: 2023/10/29 09:48:37 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	int				length;
	unsigned char	a_c;

	a_c = (unsigned char)c;
	length = write(1, &a_c, 1);
	return (length);
}

int	ft_putstr(char *str)
{
	int	length;
	int	temp_len;

	length = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[length])
	{
		temp_len = ft_putchar(str[length]);
		if (temp_len == -1)
		{
			length = -1;
			break ;
		}
		length += temp_len;
	}
	return (length);
}

int	ft_putpercent(void)
{
	int	percent;
	int	length;

	length = 0;
	percent = 37;
	length = write(1, &percent, 1);
	return (length);
}

int	ft_putint(int n)
{
	char	*str;
	int		length;

	str = ft_itoa(n);
	length = ft_putstr(str);
	if (str)
		free(str);
	else
		length = -1;
	return (length);
}

int	ft_putuint(unsigned int n)
{
	char	*str;
	int		length;

	str = ft_uitoa(n);
	length = ft_putstr(str);
	if (str)
		free(str);
	else
		length = -1;
	return (length);
}
