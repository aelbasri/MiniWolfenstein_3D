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
	if (data->map->map[j][i] == '2')
		*b = 4;
}
