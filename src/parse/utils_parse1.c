/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 04:37:09 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/27 11:39:44 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_check_int(char *str, int i, int *color, int *count)
{
	char	**child;
	int		n;

	if (!i)
	{
		child = ft_split(str, ' ');
		if (!child || ft_len_v1(child) != 2)
		{
			*count -= 100;
			return ;
		}
		child[1] = ft_return_num(child[1]);
		n = ft_atoi(child[1]);
		*count += (ft_len_v1(child) != 2 || ft_strcmp(ft_itoa(n), child[1])
				|| n > 255);
		*color += n << 16;
	}
	else
	{
		str = ft_strtrim(ft_return_num(str), " ");
		n = ft_atoi(str);
		*color += (i == 1) * (n << 8) + (i != 1) * n;
		*count += (n > 255 || ft_strcmp(ft_itoa(n), str)) * 1;
	}
}

void	ft_check_num(char *num, int *color, int *count)
{
	char	**ss;
	int		i;

	i = 0;
	ss = ft_split(num, ',');
	*count += ((ft_len_v1(ss) != 3) * -110);
	while (ss[i])
	{
		ft_check_int(ss[i], i, color, count);
		i++;
	}
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
		ft_check_num(tr, &map->C, &count);
	else
		ft_check_num(tr, &map->F, &count);
	return (count);
}

int	ft_path(char *str, t_map *map)
{
	char	**ss;
	int		count;

	count = 0;
	ss = ft_split(str, ' ');
	if (ft_len_v1(ss) != 2 || !ss[1])
		return (-20);
	if (!ft_strcmp(ss[0], "NO") && !chpath(ss[1], ".xpm") && ++count)
		map->no = ft_strdup(ss[1]);
	else if (!ft_strcmp(ss[0], "SO") && !chpath(ss[1], ".xpm"))
	{
		count += 2;
		map->so = ft_strdup(ss[1]);
	}
	else if (!ft_strcmp(ss[0], "WE") && !chpath(ss[1], ".xpm"))
	{
		count += 3;
		map->we = ft_strdup(ss[1]);
	}
	else if (!ft_strcmp(ss[0], "EA") && !chpath(ss[1], ".xpm"))
	{
		count += 4;
		map->ea = ft_strdup(ss[1]);
	}
	return (count);
}

int	check_space(char **map, int i, int j)
{
	int		count;
	char	c;
	int		n;

	count = 0;
	c = map[i][j];
	if (c == ' ' && !((!map[i][j] || ft_strchr("1 ", map[i][j + 1])) && (!j
				|| ft_strchr("1 ", map[i][j - 1])) && (!map[i + 1]
				|| ft_strchr("1 ", map[i + 1][j])) && (!i || ft_strchr("1 ",
					map[i - 1][j]))))
		count++;
	else if (!j || !map[i][j + 1] || !i || !map[i + 1])
		count += (!ft_strchr("1 ", c) * 4);
	else if (c == '2' || c == '3')
	{
		n = map[i][j + 1] - 48;
		count -= !((map[i][j + 1] == (48 + n) && map[i][j - 1] == (48 + n))
				&& (map[i + 1][j] == (48 + !n) && map[i - 1][j] == (48 + !n)));
	}
	else
	{
		map[i][j] = (ft_strchr("NOSE", c) * '0' + !ft_strchr("NOSE", c) * c);
		count += ft_strchr("NOSE", c);
	}
	return (count);
}
