/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelbassat <abdelbassat@student.42.fr>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-27 09:39:22 by abdelbassat       #+#    #+#             */
/*   Updated: 2024-07-27 09:39:22 by abdelbassat      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("--%s--\n", str[i]);
		i++;
	}
}

char	*ft_join(char *str, int max)
{
	int		i;
	char	*arr;
	int		len;

	i = 0;
	len = ft_strlen(str);
	arr = malloc(sizeof(char *) * (max + 1));
	while (str[i] || i < max)
	{
		arr[i] = (i < len) * str[i] + (!(i < len) * 32);
		i++;
	}
	arr[i] = 0;
	return (free(str), arr);
}

int	ChPath(char *file, char *ex)
{
	int	fd;
	int	res;

	res = -2;
	if (!strcmp(ft_strrchr(file, '.'), ex) && (fd = open(file, O_RDONLY)))
		res = ((fd < 0) * fd + !(fd < 0) * 0);
	return (res);
}

char	*get_next_line(char *file)
{
	char	*buff;
	char	*data;
	int		fd;

	buff = malloc(2);
	data = NULL;
	fd = open(file, O_RDONLY);
	while (1)
	{
		if (!read(fd, buff, 1))
			break ;
		buff[1] = 0;
		data = ft_strjoin(data, buff);
	}
	return (free(buff), close(fd), data);
}

int	ft_jock(char **str, int flag)
{
	int	i;

	i = 0;
	if (!flag)
	{
		while (str[i])
			free(str[i++]);
		free(str);
		i = 0;
	}
	else
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	ft_print_err(int er)
{
	if (er == -1)
		perror("CUB3D ");
	else if (er == -2)
		ft_putstr_fd("extention Error\n", 2);
	return (er);
}

int	ft_check_num(char *num, int *color)
{
	char	**ss;
	int		count;
	char	**child;
	int		i;
	int		n;

	i = 0;
	ss = ft_split(num, ',');
	count = (ft_jock(ss, 2) == 3) * 0 + ((ft_jock(ss, 2) != 3) * 10);
	while (ss[i] && !count)
	{
		if (!i)
		{
			child = ft_split(ss[i], ' ');
			if (ft_jock(child, 2) != 2 || ft_atoi(child[1]) > 255)
				count++;
			*color += ft_atoi(child[1]) * 65536;
		}
		else
		{
			n = ft_atoi(ss[i]);
			*color += (i == 1) * (n * 256) + (i != 1) * n;
			count += ((n <= 255) * 0 + (n > 255) * 1);
		}
		i++;
	}
	count = count + ft_jock(child, 0) + ft_jock(ss, 0);
	return (count);
}

int	ft_check_char(char *str, t_map *map)
{
	int		i;
	int		count;
	char	*tr;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strchr("0123456789 ,CF", str[i]))
			count++;
		if (ft_strchr("C,", str[i]) || (str[i] == 'F' && ++count))
			count++;
		i++;
	}
	tr = ft_strtrim(str, " ");
	if (count == 3)
		count += ft_check_num(tr, &map->C);
	else
		count += ft_check_num(tr, &map->F);
	return (free(tr), count);
}

int	ft_path(char *str, t_map *map)
{
	char	**ss;
	int		flag;

	flag = 0;
	ss = ft_split(str, ' ');
	if (!ss[1])
		return (-20);
	if (!strcmp(ss[0], "NO") && !ChPath(ss[1], ".xpm") && ++flag)
		map->no = ft_strdup(ss[1]);
	else if (!strcmp(ss[0], "SO") && !ChPath(ss[1], ".xpm") && (flag += 2))
		map->so = ft_strdup(ss[1]);
	else if (!strcmp(ss[0], "WE") && !ChPath(ss[1], ".xpm") && (flag += 3))
		map->we = ft_strdup(ss[1]);
	else if (!strcmp(ss[0], "EA") && !ChPath(ss[1], ".xpm") && (flag += 4))
		map->ea = ft_strdup(ss[1]);
	flag = flag + ft_jock(ss, 0);
	return (flag);
}

int	Check_space(char **map, int i, int j)
{
	int		count;
	char	c;

	count = 0;
	c = map[i][j];
	if (c == ' ' && !((!map[i][j] || ft_strchr("1 ", map[i][j + 1])) && (!j
				|| ft_strchr("1 ", map[i][j - 1])) && (!map[i + 1]
				|| ft_strchr("1 ", map[i + 1][j])) && (!i || ft_strchr("1 ",
					map[i - 1][j]))))
		count++;
	else if (!j || !map[i][j + 1] || !i || !map[i + 1])
		count += !ft_strchr("1 ", c);
	else
	{
		map[i][j] = (ft_strchr("NOSE", c) * '0' + !ft_strchr("NOSE", c) * c);
		count += ft_strchr("NOSE", c);
	}
	return (count);
}

int	ft_parse_map(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			count += Check_space(map, i, j);
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
		if (ft_strchr("NOSE", str[i]) && (map->x = i + 1) && (map->y = j + 1))
			break ;
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
	ss = ft_split(str, '\n');
	max = 0;
	while (ss[i])
	{
		num = ft_strlen(ss[i]);
		if (num > max)
			max = num;
		i++;
	}
	i = 0;
	while (ss[i])
	{
		ss[i] = ft_join(ss[i], max);
		ft_pos(ss[i], map, i);
		i++;
	}
	map->x_win = max;
	map->y_win = i;
	return (ss);
}
int	ft_Read_Map(char *file, t_map *map)
{
	char	**rd_file;
	char	*strtrim;
	int		i;
	int		count;
	char	*join;

	count = 0;
	if (ft_print_err(ChPath(file, ".cub")))
		return (1);
	join = get_next_line(file);
	rd_file = ft_split(join, '\n');
	free(join);
	join = NULL;
	i = 0;
	while (rd_file && rd_file[i])
	{
		strtrim = ft_strtrim(rd_file[i], " ");
		if (ft_strchr(rd_file[i], '.'))
			count += ft_path(rd_file[i], map);
		else if (ft_strchr(rd_file[i], ','))
			count += ft_check_char(rd_file[i], map);
		else if (*strtrim)
			join = ft_strjoin(join, rd_file[i]);
		join = ft_strjoin(join, "\n");
		free(strtrim);
		i++;
	}
	map->map = ft_convertt(join, map);
	count += ft_parse_map(map->map) + ft_jock(rd_file, 0);
	// count += 10;
	return (free(join), (count == 17) * 0 + (count != 17) * 1);
}
