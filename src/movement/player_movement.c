/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:33:08 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/21 21:33:11 by aelbasri         ###   ########.fr       */
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
	&& data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '2')
		return (1);
	return (0);
}

void	player_movement(t_data *data)
{
	double	x;
	double	y;
	double	angle;
	int		flag;
	int		i;

	i = 0;
	normalize(&(data->player->angle));
	y = data->player->py + (3 * sin(data->player->angle + (data->movement_flag \
	* (M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed);
	x = data->player->px + (3 * cos(data->player->angle + (data->movement_flag \
	* (M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed);
	angle = data->player->angle;
	while (i < 12)
	{
		flag = check_and_move(data, angle);
		if (flag == 0)
			break ;
		angle += 30 * M_PI / 180;
		i++;
	}
	if (flag != 0 && (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != \
	'1' && data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '2'))
	{
		data->player->py += sin(data->player->angle + (data->movement_flag * \
		(M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed;
		data->player->px += cos(data->player->angle + (data->movement_flag * \
		(M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed;
	}
	else
	{
		y = data->player->py + (3 * sin(data->player->angle + (data->movement_flag\
		* (M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2));
		x = data->player->px + (3 * cos(data->player->angle + (data->movement_flag * \
		(M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2));
		if (data->map->map[(int)(y / T_SIZE)][(int)(data->player->px / T_SIZE)] != '1'\
		 && data->map->map[(int)(y / T_SIZE)][(int)(data->player->px / T_SIZE)] != '2')
			data->player->py += sin(data->player->angle + (data->movement_flag * (M_PI / 2)))\
			 * (data->player->walk_dir) * (data->player->p_speed / 2);
		if (data->map->map[(int)(data->player->py / T_SIZE)][(int)(x / T_SIZE)] != '1'\
		&& data->map->map[(int)(data->player->py / T_SIZE)][(int)(x / T_SIZE)] != '2')
			data->player->px += cos(data->player->angle + (data->movement_flag * \
			(M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2);
	}
	data->movement_flag = 0;
}

int	update_player(int key_code, t_data *data)
{
	if(key_code == 'f')
        data->flag_v1 = 1;
	else if (key_code == LF_KEY)
		data->player->angle = data->player->angle - (4 * (M_PI / 180));
	else if (key_code == RT_KEY)
		data->player->angle = data->player->angle + (4 * (M_PI / 180));
	else if (key_code == S_KEY)
		data->player->walk_dir = -1;
	else if (key_code == A_KEY)
	{
		data->movement_flag = -1;
		data->player->walk_dir = 1;
	}
	else if (key_code == W_KEY)
		data->player->walk_dir = 1;
	else if (key_code == UP_KEY)
		open_door(data);
	else if (key_code == D_KEY)
	{
		data->movement_flag=1; 
		data->player->walk_dir = 1;
	}
	else if (key_code == ESC_KEY)
	{
		ft_exit(data);
	}
	return (0); 
}
