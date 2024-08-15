/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 08:29:59 by abdelbassat       #+#    #+#             */
/*   Updated: 2024/08/15 10:48:26 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"



void put_square(t_data *data, int x, int y, int size, int color)
{
	int xi = 0;
	int yi = 0;
	int ex = x + size;
	int	ey = y + size;

    while (yi < ey && yi <= data->hi)
    {
		xi = 0;
        while (xi < ex && xi <= data->wi)
        {
			if ((xi >= x && xi < ex) && (yi >= y && yi < ey))
            {
                if (xi == 0 || yi == 0 || xi == ex - 1 || yi == ey - 1)
                    my_mlx_pixel_put(data->img, xi, yi, 0x00000000);	
                else
                my_mlx_pixel_put(data->img, xi, yi, color);		
            }
            xi++;
        }
        yi++;
    }
}



void    mini_map(t_data *data)
{
	int		i = 0;
    int     j = 0;
    // abdo
    double x = (data->player->px) / S_WALL ; 
    double y = (data->player->py)  / S_WALL ;
    int color = 0;
    int flag = 0;

    int x1 = ft_strlen(&data->map->map[(int)y][(int)x]);
    int y1 = ft_jock(data->map->map , 3) - (int)y;

    
    i = !(x - 10 < 0) * (x - 10) - (x1 < 10) * (10 - x1);
    j = !((y - 4) < 0) * (y - 4) - (y1 < 4) * (4 - y1);
    
    i =  (i < 0) * 0  +  !(i < 0) * i;   
    j =  (j < 0) * 0  +  !(j < 0) * j;   


    
    x -= i;
    y -= j;
    
    x1 = 0;
    y1 = 0;
	while(y1 < 8)
	{
     x1 = 0;
        while(x1 < 20)
        {
            if(!flag && (!data->map->map[j + y1] || !data->map->map[j + y1 ][i + x1]))
                flag = 1;
            if (!flag  && data->map->map[j + y1][i + x1] == '1' )
                color = 8612715;
            else 
                color =  flag * 8612715 + !flag * 458751 ;
              put_square(data, x1 * 20, y1 * 20, 20, color);
            x1++;
        }
        if(data->map->map[j + y1])
             flag = 0;
        y1++;
    }
    put_square(data, (x * 20) - 4, (y * 20) - 4, 8, 11);

    // put_square(data, data->player->px - 2.0, data->player->py - 2.0, 4.0, 0xFF00000);
    // line(data, 16, 0xFF00000);
    /* draw_rays(data); */
}
