/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:48:59 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/23 11:49:01 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_ray	*ray_create(t_data *data, double angle)
{
	t_ray_cast	cast;
	t_ray		*ray;

	normalize(&(angle));
	ray = (t_ray *)malloc(sizeof(t_ray));
	check_direction_horizontal(&cast, data, angle);
	get_intersections_horizontal(&cast, ray, data, angle);
	check_direction_vertical(&cast, data, angle);
	get_intersections_vertical(&cast, ray, data, angle);
	if (sqrt((pow(ray->x - data->player->px, 2) + \
	pow((double)(cast.y_init * T_SIZE) - data->player->py, 2))) \
	< sqrt((pow(data->player->px - (double)(cast.x_init * \
	T_SIZE), 2) + pow(data->player->py - ray->y, 2))))
	{
		ray->inter_d = HORIZONTAL;
		ray->y = (double)(cast.y_init * T_SIZE);
	}
	else
	{
		ray->inter_d = VERTICAL;
		ray->x = (double)(cast.x_init * T_SIZE);
	}
	ray->angle = angle;
	ray->next = NULL;
	return (ray);
}

void	ray_casting(t_data *data)
{
	double	tmp;
	t_ray	*ray;
	int		i;

	i = 0;
	normalize(&(data->player->angle));
	tmp = data->player->angle;
	data->player->angle = data->player->angle - (F_VIEW / 2);
	while (i < data->wi)
	{
		if (i == 0)
		{
			ray = ray_create(data, data->player->angle);
			data->ray = ray;
		}
		else
		{
			ray->next = ray_create(data, data->player->angle);
			ray = ray->next;
		}
		data->player->angle += F_VIEW / data->wi;
		i++;
	}
	data->rays_nbr = i;
	data->player->angle = tmp;
}
