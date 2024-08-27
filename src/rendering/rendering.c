/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:01:31 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/27 12:11:57 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

void	setup_add_img(t_data *data, int i, char *texturs)
{
	data->walls[i].img = mlx_xpm_file_to_image(data->mlx, texturs, \
	&(data->text_x), &(data->text_y));
	data->walls[i].addr = mlx_get_data_addr(data->walls[i].img, \
	&(data->walls[i].bits_per_pixel), \
	&(data->walls[i].line_length), &(data->walls[i].endian));
}

void	setup_testures(t_data *data)
{
	setup_add_img(data, 0, data->map->so);
	setup_add_img(data, 1, data->map->we);
	setup_add_img(data, 2, data->map->ea);
	setup_add_img(data, 3, data->map->no);
	setup_add_img(data, 4, "./utils/assets/55.xpm");
	setup_add_img(data, 5, "./utils/assets/69.xpm");
	if (!(data->walls[0].img) || !(data->walls[1].img) \
	|| !(data->walls[2].img) || !(data->walls[3].img \
	|| !(data->walls[4].img) || !(data->walls[5].img)))
	{
		printf("Error: assets\n");
		exit(2);
	}
}

void	render_all(t_data *data)
{
	data->flag = 1;
	player_movement(data);
	ray_casting(data);
	render_walls(data);
	mini_map(data);
	ft_sprit(data);
}

int	draw_map(t_data *data)
{
	t_ray	*tmp1;
	t_ray	*ray;

	mlx_destroy_image(data->mlx, data->img->img);
	data->img->img = mlx_new_image(data->mlx, data->wi, data->hi);
	data->img->addr = mlx_get_data_addr(data->img->img, \
	&(data->img->bits_per_pixel), \
	&(data->img->line_length), &(data->img->endian));
	if (data->flag == 0)
		init_player(data, data->map->p, (data->map->x - 1) \
		* T_SIZE, (data->map->y - 1) * T_SIZE);
	render_all(data);
	mouse_movement(data);
	ray = data->ray;
	while (ray)
	{
		tmp1 = ray->next;
		free(ray);
		ray = tmp1;
	}
	data->ray = NULL;
	return (0);
}
