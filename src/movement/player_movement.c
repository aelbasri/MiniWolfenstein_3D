/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 21:33:08 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/26 15:27:15 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
	while (i++ < 12)
	{
		flag = check_and_move(data, angle);
		if (flag == 0)
			break ;
		angle += 30 * M_PI / 180;
	}
	if (flag != 0 && check_valid_position(data, \
	(int)(x / T_SIZE), (int)(y / T_SIZE)) == 1)
		move_1(data);
	else
		move_2(data);
}

int	update_player(int key_code, t_data *data)
{
	static int	j;

	if (!j)
		return (j++, 0);
	if (key_code == 'f')
		data->flag_v1 = !data->flag_v1;
	else if (key_code == UP_KEY)
		open_door(data);
	else if (key_code == ESC_KEY)
		ft_exit(data);
	data->movement_flag = (key_code == A_KEY) * -1 + (key_code == D_KEY) \
	+ !(key_code == A_KEY || key_code == D_KEY) * data->movement_flag;
	data->player->angle += ((key_code == LF_KEY) * -1 + \
	(key_code == RT_KEY)) * (4 * (M_PI / 180));
	data->player->walk_dir = (key_code == D_KEY || key_code == A_KEY \
	|| key_code == W_KEY) + (key_code == S_KEY) * -1;
	return (0);
}
