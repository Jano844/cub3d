/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:35:49 by slippert          #+#    #+#             */
/*   Updated: 2023/10/29 09:50:11 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *res_buf, char *temp_buf)
{
	temp_buf = ft_strjoin(res_buf, temp_buf);
	free(res_buf);
	return (temp_buf);
}
