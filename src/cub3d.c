#include "../include/cub3d.h"

int main(int ac, char **av)
{
    t_data  data;
	// char	*tmp1;
    // char    *s;
    // int     i;
    // void *img;
    // t_map	map;

    data.map = NULL;
    data.flag = 0;
    data.row_len = 0;
    data.column_len = 0;
    data.map = malloc(sizeof(t_map));
    if (ac != 2 || ft_Read_Map(av[1], data.map))
	{
		printf("Error\n");
		return (2);
	}
    init(&data);
    data.img->img = mlx_new_image(data.mlx, data.wi, data.hi);
    data.img->addr = mlx_get_data_addr(data.img->img, &(data.img->bits_per_pixel), &(data.img->line_length), &(data.img->endian));
    setup_testures(&data);
    ft_setup(&data);
	mlx_hook(data.win, 2, 1L<<0, &update_player, &data);
    mlx_loop_hook(data.mlx, draw_map , &data);
    mlx_loop(data.mlx);
}
