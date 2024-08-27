/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:36:13 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/27 11:39:36 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*ft_join(char *str, int max)
{
	int		i;
	char	*arr;
	int		len;

	i = 0;
	len = ft_strlen(str);
	arr = ft_malloc(sizeof(char *) * (max + 1));
	while (str[i])
	{
		arr[i] = str[i];
		i++;
	}
	while (i < max)
	{
		arr[i] = 32;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

int	ft_len_v1(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	chpath(char *file, char *ex)
{
	int	fd;
	int	res;

	res = -2;
	if (!ft_strcmp(ft_strrchr(file, '.'), ex))
	{
		fd = open(file, O_RDONLY);
		res = ((fd < 0) * fd + !(fd < 0) * 0);
	}
	return (res);
}

char	*get_next_line(char *file)
{
	char	*buff;
	char	*data;
	int		fd;

	buff = ft_malloc(2);
	data = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		if (!read(fd, buff, 1))
			break ;
		buff[1] = 0;
		data = ft_strjoin(data, buff);
	}
	return (close(fd), data);
}
