/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:39:59 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/27 14:53:35 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	my_mlx_pixel_put_v1(t_img *data, int x, int y)
{
	int		color;
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	ft_setup(t_data *data)
{
	int		x;
	int		y;
	int		i;
	char	*join;

	data->animation = ft_malloc(sizeof(t_img) * (31));
	x = 0;
	y = 0;
	i = 0;
	while (i < 31)
	{
		join = ft_strjoin("./utils/bb/", ft_itoa(i + 1));
		join = ft_strjoin(join, ".xpm");
		data->animation[i].img = mlx_xpm_file_to_image(data->mlx, join, &x, &y);
		if (!data->animation[i].img)
			ft_exit(data);
		data->animation[i].addr = mlx_get_data_addr(data->animation[i].img,
				&(data->animation[i].bits_per_pixel),
				&(data->animation[i].line_length),
				&(data->animation[i].endian));
		i++;
	}
}

void	ft_render_img(t_data *data, t_img *img)
{
	int	color;
	int	u;
	int	k;

	u = 0;
	k = 0;
	while (k < 600)
	{
		u = 0;
		while (u < 1160)
		{
			color = my_mlx_pixel_put_v1(img, u, k);
			if (color >= 0)
				my_mlx_pixel_put(data->img, u, k + (700 - 600), color);
			u++;
		}
		k++;
	}
}

void	ft_sprit(t_data *data)
{
	static int	j;
	static int	i;
	int			counter;
	static int	flag = 1;

	counter = (i >= 4 && i <= 22) * 3 + !(i >= 4 && i <= 22) * 9;
	j++;
	if (j == counter)
	{
		i += flag;
		j = 0;
	}
	ft_render_img(data, &data->animation[i]);
	if (data->flag_v1)
		flag = (i >= 30) * (-1) + (i <= 23) + (i > 23 && i < 30) * flag;
	else
	{
		flag = 1;
		i = !(i >= 4) * i;
	}
}
