/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:31 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/26 15:23:07 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	one_wall_rendering(t_data *data, int j, t_ray *ray)
{
	t_render	render;

	render.i = 0;
	render.distance = sqrt((pow((data->player->px - ray->x), 2) + pow((data->player->py - ray->y), 2))) \
			* cos(ray->angle - data->player->angle + 0.00001);
	render.wall_height = data->hi * T_SIZE / render.distance;
	render.a = (data->hi - render.wall_height) / 2;
	while (render.i <= data->hi)
	{
		if (render.i >= 0 && render.i < render.a)
			my_mlx_pixel_put(data->img, j, render.i, data->map->C);
		else if (render.i >= render.a && render.i <= render.a + render.wall_height)
		{
			get_x(&render.b, &render.x, ray, data);
			render.y = render.i - render.a;
			render.color = *((unsigned int *)(data->walls[render.b].addr + ((int)((data->text_y * render.y) / render.wall_height) * (data->walls[render.b].line_length) + (int)((data->text_x * render.x) / T_SIZE) * (data->walls[render.b].bits_per_pixel / 8))));
			my_mlx_pixel_put(data->img, j, render.i, render.color);
		}
		else
			my_mlx_pixel_put(data->img, j, render.i, data->map->F);
		render.i++;
	}
}

void	render_walls(t_data *data)
{
	t_ray	*tmp;
	int		i;

	tmp = data->ray;
	i = 0;
	while (tmp)
	{
		one_wall_rendering(data, i, tmp);
		tmp = tmp->next;
		i++;
	}
}

void	setup_testures(t_data *data)
{
	data->walls[0].img = mlx_xpm_file_to_image(data->mlx, data->map->so, &(data->text_x), &(data->text_y));
	data->walls[0].addr = mlx_get_data_addr(data->walls[0].img, &(data->walls[0].bits_per_pixel), &(data->walls[0].line_length), &(data->walls[0].endian));
	data->walls[1].img = mlx_xpm_file_to_image(data->mlx, data->map->we, &(data->text_x), &(data->text_y));
	data->walls[1].addr = mlx_get_data_addr(data->walls[1].img, &(data->walls[1].bits_per_pixel), &(data->walls[1].line_length), &(data->walls[1].endian));
	data->walls[2].img = mlx_xpm_file_to_image(data->mlx, data->map->ea, &(data->text_x), &(data->text_y));
	data->walls[2].addr = mlx_get_data_addr(data->walls[2].img, &(data->walls[2].bits_per_pixel), &(data->walls[2].line_length), &(data->walls[2].endian));
	data->walls[3].img = mlx_xpm_file_to_image(data->mlx, data->map->no, &(data->text_x), &(data->text_y));
	data->walls[3].addr = mlx_get_data_addr(data->walls[3].img, &(data->walls[3].bits_per_pixel), &(data->walls[3].line_length), &(data->walls[3].endian));
	data->walls[4].img = mlx_xpm_file_to_image(data->mlx, "./utils/assets/55.xpm", &(data->text_x), &(data->text_y));
	data->walls[4].addr = mlx_get_data_addr(data->walls[4].img, &(data->walls[4].bits_per_pixel), &(data->walls[4].line_length), &(data->walls[4].endian));
	data->walls[5].img = mlx_xpm_file_to_image(data->mlx, "./utils/assets/69.xpm", &(data->text_x), &(data->text_y));
	data->walls[5].addr = mlx_get_data_addr(data->walls[5].img, &(data->walls[5].bits_per_pixel), &(data->walls[5].line_length), &(data->walls[5].endian));
	if (!(data->walls[0].img) || !(data->walls[1].img) || !(data->walls[2].img) || \
	!(data->walls[3].img || !(data->walls[4].img) || !(data->walls[5].img)))
	{
		printf("Error: assets\n");
		exit(2);
	}
}

int	draw_map(t_data *data)
{
	int  x ;
	int y ;
	x  = 0;
	y = 0;
	mlx_destroy_image(data->mlx, data->img->img);
	data->img->img = mlx_new_image(data->mlx, data->wi, data->hi);
	data->img->addr = mlx_get_data_addr(data->img->img, &(data->img->bits_per_pixel), &(data->img->line_length), &(data->img->endian));
	if (data->flag == 0)
		init_player(data, data->map->p, (data->map->x - 1) * T_SIZE, (data->map->y - 1) * T_SIZE);
	data->flag = 1;
	player_movement(data);
	ray_casting(data);
	render_walls(data);
	mini_map(data);
	ft_sprit(data);

	 mlx_mouse_get_pos(data->mlx  ,data->win , &x , &y);
    data->player->angle = data->player->angle + (-(data->x - x) * (M_PI / 180));
    mlx_mouse_get_pos(data->mlx  ,data->win , &data->x , &data->y);

	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
	t_ray *tmp1;
	t_ray *ray;

	ray = data->ray;
	while (ray)
	{
		tmp1 = ray->next;
		free(ray);
		ray = tmp1;
	}
	data->ray = NULL;
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	return (0);
}
