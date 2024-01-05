/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slippert <slippert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 20:26:05 by slippert          #+#    #+#             */
/*   Updated: 2023/10/29 09:50:17 by slippert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *res_buf)
{
	int		i;
	int		j;
	int		length;
	char	*rem_buf;

	i = 0;
	while (res_buf[i] && res_buf[i] != '\n')
		i++;
	if (!res_buf[i])
		return (free(res_buf), NULL);
	length = 0;
	while (res_buf[length])
		length++;
	rem_buf = ft_calloc(length - i + 1, sizeof(char));
	if (!rem_buf)
		return (NULL);
	i++;
	j = 0;
	while (res_buf[i])
		rem_buf[j++] = res_buf[i++];
	return (free(res_buf), rem_buf);
}

char	*ft_line(char *res_buf)
{
	char	*line;
	int		i;
	int		extra_storage;

	if (!res_buf[0])
		return (NULL);
	i = 0;
	while (res_buf[i] && res_buf[i] != '\n')
		i++;
	extra_storage = 2;
	if (res_buf[i] != '\n')
		extra_storage = 1;
	line = ft_calloc(i + extra_storage, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (res_buf[i] && res_buf[i] != '\n')
	{
		line[i] = res_buf[i];
		i++;
	}
	if (res_buf[i] && res_buf[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_read_file(int fd, char *res_buf)
{
	char	*temp_buf;
	int		bytes;

	if (!res_buf)
		res_buf = ft_calloc(1, sizeof(char));
	if (!res_buf)
		return (NULL);
	temp_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buf)
		return (free(res_buf), NULL);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, temp_buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(temp_buf), NULL);
		temp_buf[bytes] = '\0';
		res_buf = ft_strjoin_free(res_buf, temp_buf);
		if (ft_strchr(res_buf, '\n'))
			break ;
	}
	free(temp_buf);
	return (res_buf);
}

char	*get_next_line(int fd)
{
	static char	*res_buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (res_buf)
		{
			free(res_buf);
			res_buf = NULL;
		}
		return (NULL);
	}
	res_buf = ft_read_file(fd, res_buf);
	if (!res_buf)
		return (NULL);
	line = ft_line(res_buf);
	res_buf = ft_next(res_buf);
	return (line);
}
