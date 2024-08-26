/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:46:40 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/26 23:21:50 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	normalize(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle += 2 * M_PI;
}

int	init_player(t_data *data, char angle, int x, int y)
{
	data->player = malloc(sizeof(t_player));
	data->player->angle = ((angle == 'W') * W) + ((angle == 'E') * E)
		+ ((angle == 'S') * S) + ((angle == 'N') * N);
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->movement_flag = 0;
	data->player->px = x + (T_SIZE / 2);
	data->player->py = y + (T_SIZE / 2);
	data->player->p_speed = 6;
	return (0);
}

void	open_door(t_data *data)
{
	int	x;
	int	y;

	y = data->player->py + ((4 * T_SIZE / 3) * sin(data->player->angle));
	x = data->player->px + ((4 * T_SIZE / 3) * cos(data->player->angle));
	if (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] == '2')
		data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] = '3';
	else if (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] == '3')
		data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] = '2';
}

void	ft_exit(t_data *data)
{
	t_ray	*ray;
	t_ray	*tmp;
	int		i;

	ray = data->ray;
	while (ray)
	{
		tmp = ray->next;
		free(ray);
		ray = tmp;
	}
	data->ray = NULL;
	i = 0;
	while (i < 6)
		mlx_destroy_image(data->mlx, data->walls[i++].img);
	i = 0;
	while (i < 31)
		mlx_destroy_image(data->mlx, data->animation[i++].img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_image(data->mlx, data->img->img);
	mlx_destroy_display(data->mlx);
	(free(data->img), free(data->mlx), free(data->player));
	ft_free();
	exit(1);
}

void	init(t_data *data)
{
	data->row_len = data->map->x_win;
	data->column_len = data->map->y_win;
	data->wi = 1160;
	data->hi = 700;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->wi, data->hi, "window");
	data->img = malloc(sizeof(t_img));
}
