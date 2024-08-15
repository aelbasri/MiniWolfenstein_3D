/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdelbassat <abdelbassat@student.42.fr>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-15 08:29:59 by abdelbassat       #+#    #+#             */
/*   Updated: 2024-08-15 08:29:59 by abdelbassat      ###   ########.fr       */
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
                /*if (xi == 0 || yi == 0 || xi == ex - 1 || yi == ey - 1)
                    my_mlx_pixel_put(data->img, xi, yi, 0x00000000);	
                else*/
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
    int y1 = ft_jock(data->map->map , 3);


    y1 -= (int)y;
    i = ((x - 10) < 0) * 0 + !((x - 10) < 0) * (x - 10);
    if(x1 < 10)
      i -= 10 - x1;
    j = ((y - 4) < 0) * 0 + !((y - 4) < 0) * (y - 4);
    if(y1 < 4)
        j -= 4 - y1;
    
    i = ((i) < 0) * 0 + !((i) < 0) * i;
    j = (j < 0) * 0 + (!j < 0) * i;
    x -= i;
    y -= j;
    
    printf("%d %d\n" , i , j);
    int k = 0;
    int u = 0;
	while(u < 8)
	{
     k = 0;
        while(k < 20)
        {
            if(!flag && (!data->map->map[j + u] || !data->map->map[j + u ][i + k]))
                flag = 1;
            
            if ((!flag  && data->map->map[j + u][i + k] == '1') || flag)
                color = 8612715;
            else 
                color =  458751 ;
              put_square(data, k * 20, u * 20, 20, color);
            k++;
        }
        if(data->map->map[j + u])
             flag = 0;
        u++;
    }
    put_square(data, (x * 20) - 4, (y * 20) - 4, 8, 11);

    // put_square(data, data->player->px - 2.0, data->player->py - 2.0, 4.0, 0xFF00000);
    // line(data, 16, 0xFF00000);
    /* draw_rays(data); */
}