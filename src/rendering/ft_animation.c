/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_animation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 12:39:59 by abquaoub          #+#    #+#             */
/*   Updated: 2024/08/19 12:57:25 by abquaoub         ###   ########.fr       */
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


void ft_setup(t_data *data)
{
    
    data->animation = malloc(sizeof(t_img) * (29));
    int x = 0;
    int y = 0;
    int i = 0;
    char *join;
    while(i < 29)
    {
   
            join =  ft_strjoin("./utils/bb/" , ft_itoa(i + 1));
            join = ft_strjoin(join , ".xpm");
            
            data->animation[i].img = mlx_xpm_file_to_image(data->mlx, join, &x, &y);
            data->animation[i].addr = mlx_get_data_addr(data->animation[i].img, &(data->animation[i].bits_per_pixel), &(data->animation[i].line_length), &(data->animation[i].endian));
            i++;
   
    }
    
}

// void ft_draw_snow(t_data *data)
// {

	//  int i = 0;
	// int j = 0;
	// int flag;
	// static int x  = 0;
	// while(i < 700)
	// {
	// 	x++;
	// 	flag = rand() % 1150;
	// 	if(x == 10 && flag >= 2)
	// 	{
	// 	my_mlx_pixel_put(data->img , flag + 1, i , 0xfffafa );
	// 	my_mlx_pixel_put(data->img , flag, i , 0xfffafa );
	// 	my_mlx_pixel_put(data->img , flag + 2, i , 0xfffafa );
	// 	my_mlx_pixel_put(data->img , flag - 2, i , 0xfffafa );
	// 	my_mlx_pixel_put(data->img , flag - 1, i , 0xfffafa );
	// 	if(i >= 2 && i < 700 - 2 )
	// 	{
	// 		my_mlx_pixel_put(data->img , flag , i + 1  , 0xfffafa );
	// 		my_mlx_pixel_put(data->img , flag , i + 2  , 0xfffafa );
	// 		my_mlx_pixel_put(data->img , flag , i  - 1, 0xfffafa );
	// 		my_mlx_pixel_put(data->img , flag , i  - 2, 0xfffafa );

	// 	}
	// 	}
	// 	i++;
	// }
		

	// if(x >= 10)
	// 	x = 0;
// }

void	ft_sprit(t_data *data)
{
	// char *join;
	// int flag = 0;
    static int j = 0;
	static int i = 0;
	int counter = 0;

    counter = (i >= 4 && i <= 22) * 5 + !(i >= 4 && i <= 22) * 10;
    j++;
    if(j == counter)
    {
        j = 0;
        i++;
    }
	
	int color;
	int k = 0;
	int u ;
    
	while (k < 600)
	{
		u = 0;
		while (u < 1160)
		{
			color = my_mlx_pixel_put_v1(&data->animation[i], u, k);
            if(color >= 0)
				my_mlx_pixel_put(data->img, u , k + (700 - 600)  , color);
			u++;
		}
		k++;
	}
 
    // i = (i >= 28) * 22 + !(i >= 28) * i; ;
	if(!data->flag_v1)
		i = !(i >= 4)  * i;
	else
		i = (i >= 28) * 22 +  !(i >= 28) * i;

}
