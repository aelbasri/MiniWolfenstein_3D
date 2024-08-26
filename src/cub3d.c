/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:49:29 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/26 16:21:35 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"



int	main(int ac, char **av)
{
	t_data	data;

	data.flag = 0;
	data.row_len = 0;
	data.column_len = 0;
	data.x = 0;
	data.y = 0;
	data.map = ft_malloc(sizeof(t_map));
	data.map->C = 0;
	data.map->F = 0;
	if (ac != 2 || ft_read_map(av[1], data.map))
	{
		printf("Error\n");
		return (2);
	}
	init(&data);
	data.img->img = mlx_new_image(data.mlx, data.wi, data.hi);
	data.img->addr = mlx_get_data_addr(data.img->img, \
	&(data.img->bits_per_pixel), &(data.img->line_length), &(data.img->endian));
	setup_testures(&data);
	ft_setup(&data);
    mlx_mouse_get_pos(data.mlx  ,data.win , &data.x , &data.y);

	mlx_hook(data.win, 2, 1L << 0, &update_player, &data);
	mlx_loop_hook(data.mlx, draw_map, &data);
	mlx_loop(data.mlx);
}
