/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 09:39:22 by abdelbassat       #+#    #+#             */
/*   Updated: 2024/09/05 14:55:54 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_parse_map(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_space(map, i, j, &count);
			j++;
		}
		i++;
	}
	count = ((count == 1) * 0 + (count != 1) * 1);
	return (count);
}

void	ft_pos(char *str, t_map *map, int j)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr("NWSE", str[i]))
		{
			map->x = i + 1;
			map->y = j + 1;
			map->p = str[i];
			break ;
		}
		i++;
	}
}

char	**ft_convertt(char *str, t_map *map)
{
	int		i;
	int		num;
	char	**ss;
	int		max;

	i = 0;
	max = 0;
	ss = ft_split(str, '\n');
	while (ss && ss[i])
	{
		num = ft_strlen(ss[i]);
		max = (num > max) * num + !(num > max) * max;
		i++;
	}
	i = 0;
	while (ss && ss[i])
	{
		ss[i] = ft_join(ss[i], max);
		ft_pos(ss[i], map, i);
		i++;
	}
	map->x_win = max;
	map->y_win = i;
	return (ss);
}

char	*ft_utils_read(char *file, t_map *map, int *count)
{
	char	*rd_file;
	char	*join;
	int		flag;
	int		fd;

	fd = open(file, O_RDONLY);
	flag = 0;
	rd_file = get_next_line(fd);
	join = NULL;
	while (rd_file)
	{
		if (rd_file[0] != '\n' && ft_strtrim(rd_file, "1 ")[0] == '\n')
			flag = 1;
		if (ft_strchr(rd_file, '.') && !flag)
			*count += ft_path(rd_file, map);
		else if (ft_strchr(rd_file, ',') && !flag)
			*count += ft_check_char(rd_file, map);
		else
			join = ft_strjoin(join, rd_file);
		*count += (rd_file[0] == '\n' && flag) * 200;
		rd_file = get_next_line(fd);
	}
	return (join);
}

int	ft_read_map(char *file, t_map *map)
{
	int		count;
	char	*join;

	count = 0;
	if (chpath(file, ".cub"))
		return (1);
	join = ft_utils_read(file, map, &count);
	map->map = ft_convertt(join, map);
	count += ft_parse_map(map->map);
	if (!map->no || !map->so || !map->ea || !map->we)
		count += 100;
	return ((count != 17) * 1);
}
