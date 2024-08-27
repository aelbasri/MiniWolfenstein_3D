/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:29:59 by abdelbassat       #+#    #+#             */
/*   Updated: 2024/08/27 12:07:36 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	line(t_data *data, double x, double y)
{
	double	steps;
	double	i;
	t_line	line;

	i = 0;
	line.x2 = (data->player->px) + (20 * cos(data->player->angle));
	line.y2 = (data->player->py) + (20 * sin(data->player->angle));
	line.xs = line.x2 - data->player->px;
	line.ys = line.y2 - data->player->py;
	steps = fmax(fabs(line.xs), fabs(line.ys));
	line.xi = line.xs / steps;
	line.yi = line.ys / steps;
	while (i <= steps && (x >= 0 && x < data->row_len * 16) && ((y >= 0
				&& y < data->column_len * 16)))
	{
		my_mlx_pixel_put(data->img, x, y, 0x994C00);
		x = x + line.xi;
		y = y + line.yi;
		i++;
	}
}

void	put_square(t_data *data, int x, int y, int color)
{
	int	xi;
	int	yi;
	int	ex;
	int	ey;
	int	size;

	size = 20;
	if (color == 0x994C00)
		size = 8;
	xi = 0;
	yi = 0;
	ex = x + size;
	ey = y + size;
	while (yi < ey && yi <= data->hi)
	{
		xi = 0;
		while (xi < ex && xi <= data->wi)
		{
			if ((xi >= x && xi < ex) && (yi >= y && yi < ey))
				my_mlx_pixel_put(data->img, xi, yi, color);
			xi++;
		}
		yi++;
	}
}

void	draw_minimap(t_data *data, int i, int j)
{
	int		x1;
	int		y1;
	char	c;
	int		color;

	x1 = 0;
	y1 = 0;
	while (y1 < data->map->y_win && y1 < MINI_Y)
	{
		x1 = 0;
		while (x1 < data->map->x_win && x1 < MINI_X)
		{
			c = data->map->map[j + y1][i + x1];
			color = (c == '3') * 65280 + (c == '2') * 16711680 + (c == '1')
				* 734550 + (c == '0' || c == ' ') * 15496470;
			put_square(data, x1 * 20, y1 * 20, color);
			x1++;
		}
		y1++;
	}
}

void	mini_map(t_data *data)
{
	int		i;
	int		j;
	double	x;
	double	y;

	x = (data->player->px) / T_SIZE;
	y = (data->player->py) / T_SIZE;
	i = ft_strlen(&data->map->map[(int)y][(int)x]);
	j = ft_len_v1(data->map->map) - (int)y;
	i = !(x - MINI_X / 2 < 0) * (x - MINI_X / 2) - (i < MINI_X / 2) * (MINI_X
			/ 2 - i);
	j = !(y - MINI_Y / 2 < 0) * (y - MINI_Y / 2) - (j < MINI_Y / 2) * (MINI_Y
			/ 2 - j);
	i = (i > 0) * i;
	j = (j > 0) * j;
	x -= i;
	y -= j;
	draw_minimap(data, i, j);
	put_square(data, (x * 20) - 4, (y * 20) - 4, 0x994C00);
	line(data, (x * 20), (y * 20));
}
