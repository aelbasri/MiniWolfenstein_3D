/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:42:18 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/26 22:42:20 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_and_move(t_data *data, double angle)
{
	double	x;
	double	y;

	y = data->player->py + (3 * sin(angle));
	x = data->player->px + (3 * cos(angle));
	if (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '1' \
	&& data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '2' \
	&& data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != ' ')
		return (1);
	return (0);
}

int	check_valid_position(t_data *data, int x, int y)
{
	if (y < data->column_len && \
		x < data->row_len && \
		data->map->map[y][x] != '1' && \
		data->map->map[y][x] != '2' && \
		data->map->map[y][x] != ' ')
		return (1);
	return (0);
}

void	move_1(t_data *data)
{
	data->player->py += sin(data->player->angle + \
	(data->movement_flag * (M_PI / 2))) * \
	(data->player->walk_dir) * data->player->p_speed;
	data->player->px += cos(data->player->angle + \
	(data->movement_flag * (M_PI / 2))) * \
	(data->player->walk_dir) * data->player->p_speed;
	data->movement_flag = 0;
}

void	move_2(t_data *data)
{
	double	x;
	double	y;

	y = data->player->py + (3 * sin(data->player->angle + \
	(data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) \
	* (data->player->p_speed / 2));
	x = data->player->px + (3 * cos(data->player->angle + \
	(data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * \
	(data->player->p_speed / 2));
	if (check_valid_position(data, \
	(int)(data->player->px / T_SIZE), (int)(y / T_SIZE)) == 1)
		data->player->py += sin(data->player->angle + \
		(data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) \
		* (data->player->p_speed / 2);
	if (check_valid_position(data, \
	(int)(x / T_SIZE), (int)(data->player->py / T_SIZE)) == 1)
		data->player->px += cos(data->player->angle + \
		(data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) \
		* (data->player->p_speed / 2);
	data->movement_flag = 0;
}
