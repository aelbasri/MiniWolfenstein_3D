/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:39:57 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/23 12:40:00 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	get_color(t_data *data, t_render render)
{
	return (*((unsigned int *)(data->walls[render.b].addr \
	+ ((int)((data->text_y * render.y) / render.wall_height)*\
	(data->walls[render.b].line_length) + \
	(int)((data->text_x * render.x) / T_SIZE)*\
	(data->walls[render.b].bits_per_pixel / 8)))));
}

void	one_wall_rendering(t_data *data, int j, t_ray *ray)
{
	t_render	render;

	render.i = 0;
	render.distance = sqrt((pow((data->player->px - ray->x), 2) \
	+ pow((data->player->py - ray->y), 2))) \
			* cos(ray->angle - data->player->angle + 0.00001);
	render.wall_height = data->hi * T_SIZE / render.distance;
	render.a = (data->hi - render.wall_height) / 2;
	while (render.i <= data->hi)
	{
		if (render.i >= 0 && render.i < render.a)
			my_mlx_pixel_put(data->img, j, render.i, data->map->c);
		else if (render.i >= render.a \
		&& render.i <= render.a + render.wall_height)
		{
			get_x(&render.b, &render.x, ray, data);
			render.y = render.i - render.a;
			render.color = get_color(data, render);
			my_mlx_pixel_put(data->img, j, render.i, render.color);
		}
		else
			my_mlx_pixel_put(data->img, j, render.i, data->map->f);
		render.i++;
	}
}

void	mouse_movement(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	data->player->angle = data->player->angle + (-(data->x - x) * (M_PI / 180));
	mlx_mouse_get_pos(data->mlx, data->win, &data->x, &data->y);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	get_x(int *b, double *x, t_ray *ray, t_data *data)
{
	int	j;
	int	i;

	if (ray->inter_d == VERTICAL)
	{
		if ((ray->angle >= 0 && ray->angle <= M_PI / 2) || \
		(ray->angle >= 3 * M_PI / 2 && ray->angle <= 2 * M_PI))
			*b = 2;
		else
			*b = 1;
		*x = fmod(ray->y, T_SIZE);
	}
	else
	{
		if (ray->angle >= 0 && ray->angle <= M_PI)
			*b = 3;
		else
			*b = 0;
		*x = fmod(ray->x, T_SIZE);
	}
	j = (int)((ray->y + sin(ray->angle)) / T_SIZE);
	i = (int)((ray->x + cos(ray->angle)) / T_SIZE);
	if (j < data->column_len && i < data->row_len \
	&& data->map->map[j][i] == '2')
		*b = 4;
}
