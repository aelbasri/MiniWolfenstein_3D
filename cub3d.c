#include "cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void put_square(t_data *data, int x, int y, int size, int color)
// {
// 	int xi = 0;
// 	int yi = 0;
// 	int ex = x + size;
// 	int	ey = y + size;

//     while (yi < ey && yi <= data->hi)
//     {
// 		xi = 0;
//         while (xi < ex && xi <= data->wi)
//         {
// 			if ((xi >= x && xi < ex) && (yi >= y && yi < ey))
//             {
//                 /*if (xi == 0 || yi == 0 || xi == ex - 1 || yi == ey - 1)
//                     my_mlx_pixel_put(data->img, xi, yi, 0x00000000);	
//                 else*/
//                 my_mlx_pixel_put(data->img, xi, yi, color);		
//             }
//             xi++;
//         }
//         yi++;
//     }
// }

void normalize(double *angle)
{
    *angle = fmod(*angle , (2 * M_PI));
    if (*angle < 0)
        *angle += 2 * M_PI;
}

t_ray    *ray_create(t_data *data, double angle)
{
    int x_init;
	int	x_max;
    int j = 1;
    int i;
	int y_init;
	int	y_max;
    t_ray *ray;

    normalize(&(angle));
	ray = (t_ray *)malloc(sizeof(t_ray));
    
    if (angle >= 0 && angle <= M_PI)
    {
        j = 1;
        i = 0;
        y_init = ((int)(data->player->py / T_SIZE)) + 1;
        y_max = ((int)(data->column_len));
    }
    else
    {
        y_init = ((int)(data->player->py / T_SIZE));
        y_max = 0;
        j = -1;
        i = -1;
    }
    while (y_max - (j * y_init) >= 0)
	{
		ray->x = data->player->px + ((((double)(y_init * T_SIZE)) - data->player->py) / tan(angle));
        if (ray->x < 0)
            ray->x = 0;
        if (ray->x > (data->row_len - 1) * T_SIZE)
            ray->x = (data->row_len - 1) * T_SIZE;
		if (y_init + i < 0 || y_init + i >= data->column_len || \
        data->map->map[y_init + i][(int)ray->x / T_SIZE] == '1' || \
        data->map->map[y_init + i][(int)ray->x / T_SIZE] == '2')
			break;
        y_init += j; 
    }
    if ((angle >= 0 && angle <= M_PI / 2) || (angle >= 3 * M_PI / 2 &&  angle <= 2 * M_PI))
    {
        j = 1;
        i = 0;
        x_init = ((int)(data->player->px / T_SIZE)) + 1;
        x_max = (int)(data->row_len);
    }
    else
    {
        x_init = ((int)(data->player->px / T_SIZE));
        x_max = 0;
        j = -1;
        i = -1;
    }
	while (x_max - (x_init * j) >= 0)
	{
		ray->y = data->player->py + ((((double)(x_init * T_SIZE)) - data->player->px) * tan(angle));
        if (ray->y < 0)
            ray->y = 0;
        if (ray->y > (data->column_len - 1) * T_SIZE)
            ray->y = (data->column_len - 1) * T_SIZE;
        if (x_init + i < 0 || x_init + i >= data->row_len || \
        data->map->map[(int)ray->y / T_SIZE][x_init + i] == '1' || 
        data->map->map[(int)ray->y / T_SIZE][x_init + i] == '2')
			break;
        x_init += j;
	}
    /* √((x1 - x)² + (y1 - y)²) < √((x1 - x)² + (y1 - y)²) */
	if (sqrt((pow(ray->x - data->player->px, 2) + pow((double)(y_init * T_SIZE) - data->player->py, 2))) <
		sqrt((pow(data->player->px - (double)(x_init * T_SIZE), 2) + pow(data->player->py - ray->y, 2))))
    {
        ray->inter_d = HORIZONTAL;
        ray->y = (double)(y_init * T_SIZE);
    }
    else
	{
        ray->inter_d = VERTICAL;
    	ray->x = (double)(x_init * T_SIZE);
    }
    ray->angle = angle;
    ray->next = NULL;
    return (ray);
}


void    one_wall_rendering(t_data *data, int j, t_ray *ray)
{
	double	distance;
    unsigned int color;
    double  wall_height;
    double  wall_width;
    double  a;
    int     b = 0;
    double  x;
    double  y;
    int     i;
	
    i = 0;
    x = 0;
    y = 0;
	distance = sqrt((pow((data->player->px - ray->x), 2) + pow((data->player->py - ray->y), 2))) * cos(ray->angle - data->player->angle + 0.00001);
	wall_height = data->hi * T_SIZE / distance;
    a = (data->hi - wall_height) / 2;
    i = 0;
    while (i <= data->hi)
    {
        if (i >= 0 && i < a)
            my_mlx_pixel_put(data->img, j, i, data->map->C);
        else if (i >= a && i <= a + wall_height)
        {
            if (ray->inter_d == VERTICAL)
            {
                if ((ray->angle >= 0 && ray->angle <= M_PI / 2) || (ray->angle >= 3 * M_PI / 2 &&  ray->angle <= 2 * M_PI))
                    b = 2;
                else
                    b = 1;
                x = (fmod(ray->y , T_SIZE));
            }
            else
            {

                if (ray->angle >= 0 && ray->angle <= M_PI)
                    b = 3;
                else
                    b = 0;
                x = fmod(ray->x , T_SIZE);
            }
            if (data->map->map[(int)((ray->y + sin(ray->angle)) / T_SIZE)][(int)((ray->x + cos(ray->angle)) / T_SIZE)] == '2')
                b = 4;
            /*if ((int)(((ray->x + cos(ray->angle)) / T_SIZE) - 1) >= 0 && \
            data->map->map[((int)((ray->y + sin(ray->angle)) / T_SIZE))][(int)(((ray->x + cos(ray->angle)) / T_SIZE) - 1)] == '3' || \
            (int)(((ray->x + cos(ray->angle)) / T_SIZE) + 1) < data->row_len && \
            data->map->map[((int)((ray->y + sin(ray->angle)) / T_SIZE))][(int)(((ray->x + cos(ray->angle)) / T_SIZE) + 1)] == '3' || \
            ((int)(((ray->y + sin(ray->angle)) / T_SIZE) - 1)) >= 0 && \
            data->map->map[((int)(((ray->y + sin(ray->angle)) / T_SIZE) - 1))][(int)(((ray->x + cos(ray->angle)) / T_SIZE))] == '3' || \
            ((int)(((ray->y + sin(ray->angle)) / T_SIZE) + 1)) < data->column_len && \
            data->map->map[((int)(((ray->y + sin(ray->angle)) / T_SIZE) + 1))][(int)(((ray->x + cos(ray->angle)) / T_SIZE))] == '3')
                b = 5;*/
            y = i - a;
            color = *((unsigned int*)(data->walls[b].addr + ((int)((data->text_y * y) / wall_height) * data->walls[b].line_length + (int)((data->text_x * x) / T_SIZE) * (data->walls[b].bits_per_pixel / 8))));
            my_mlx_pixel_put(data->img, j, i, color);
        }
        else
            my_mlx_pixel_put(data->img, j, i, data->map->F);
        i++;
    }
}


void    render_walls(t_data *data)
{
    t_ray *tmp;
    int     i;

    tmp = data->ray;
    i = 0;
    while (tmp)
    {
        one_wall_rendering(data, i, tmp);
        tmp = tmp->next;
        i++;
    }
}

void	ray_casting(t_data *data)
{
		double l;
		double tmp;
        t_ray   *ray;
        int i = 0;

        normalize(&(data->player->angle));
		tmp = data->player->angle;
		data->player->angle  = data->player->angle - (F_VIEW / 2);
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

int    check_and_move(t_data *data, double angle)
{
    double	x;
    double	y;

    y = data->player->py + (3 * sin(angle));
	x = data->player->px + (3 * cos(angle));
    if (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '1' && data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '2')
        return (1);
    return (0);
}

void player_movement(t_data *data)
{
    double	x;
    double	y;
    double  angle;
    int     flag;
    int     i = 0;

    normalize(&(data->player->angle));
    // printf("hello %d\n", data->movement_flag);
    y = data->player->py + (3 *sin(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed);
	x = data->player->px + (3 *cos(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed);
    angle = data->player->angle;
    while(i < 12)
    {
        flag = check_and_move(data, angle);
        if (flag == 0)
            break;
        angle += 30 * M_PI / 180;
        i++;
    }
    if (flag != 0 && (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '1' && data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] != '2'))
    {
		data->player->py += sin(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed;
		data->player->px += cos(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * data->player->p_speed;
    }
    else
    {
        y = data->player->py + (3 * sin(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2));
        x = data->player->px + (3 * cos(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2));
        if (data->map->map[(int)(y / T_SIZE)][(int)(data->player->px / T_SIZE)] != '1' && data->map->map[(int)(y / T_SIZE)][(int)(data->player->px / T_SIZE)] != '2')
            data->player->py += sin(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2);
        if (data->map->map[(int)(data->player->py / T_SIZE)][(int)(x / T_SIZE)] != '1' && data->map->map[(int)(data->player->py / T_SIZE)][(int)(x / T_SIZE)] != '2')
            data->player->px += cos(data->player->angle + (data->movement_flag * (M_PI / 2))) * (data->player->walk_dir) * (data->player->p_speed / 2);
	}
    data->movement_flag = 0;
}

int	init_player(t_data *data, char angle, int x, int y)
{
	data->player = malloc(sizeof(t_player));
    data->player->angle = ((angle == 'W') * W) + ((angle == 'E') * E) + ((angle == 'S') * S) + ((angle == 'N') * N);
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
    data->movement_flag = 0;
	data->player->px = x + (T_SIZE / 2);
	data->player->py = y + (T_SIZE / 2);
    data->player->p_speed = 6;
	return (0);
}

void    setup_testures(t_data *data)
{
    data->text_x = 0;
    data->text_y = 0;

    data->walls[0].img = mlx_xpm_file_to_image(data->mlx, data->map->so, &(data->text_x), &(data->text_y));
    data->walls[0].addr = mlx_get_data_addr(data->walls[0].img, &(data->walls[0].bits_per_pixel), &(data->walls[0].line_length), &(data->walls[0].endian));

    data->walls[1].img = mlx_xpm_file_to_image(data->mlx, data->map->we, &(data->text_x), &(data->text_y));
    data->walls[1].addr = mlx_get_data_addr(data->walls[1].img, &(data->walls[1].bits_per_pixel), &(data->walls[1].line_length), &(data->walls[1].endian));

    data->walls[2].img = mlx_xpm_file_to_image(data->mlx, data->map->ea, &(data->text_x), &(data->text_y));
    data->walls[2].addr = mlx_get_data_addr(data->walls[2].img, &(data->walls[2].bits_per_pixel), &(data->walls[2].line_length), &(data->walls[2].endian));

    data->walls[3].img = mlx_xpm_file_to_image(data->mlx, data->map->no, &(data->text_x), &(data->text_y));
    data->walls[3].addr = mlx_get_data_addr(data->walls[3].img, &(data->walls[3].bits_per_pixel), &(data->walls[3].line_length), &(data->walls[3].endian));

    data->walls[4].img = mlx_xpm_file_to_image(data->mlx, "./assets/55.xpm", &(data->text_x), &(data->text_y));
    data->walls[4].addr = mlx_get_data_addr(data->walls[4].img, &(data->walls[4].bits_per_pixel), &(data->walls[4].line_length), &(data->walls[4].endian));
    
    data->walls[5].img = mlx_xpm_file_to_image(data->mlx, "./assets/69.xpm", &(data->text_x), &(data->text_y));
    data->walls[5].addr = mlx_get_data_addr(data->walls[5].img, &(data->walls[5].bits_per_pixel), &(data->walls[5].line_length), &(data->walls[5].endian));

    if (!(data->walls[0].img) || !(data->walls[1].img) || !(data->walls[2].img) || !(data->walls[3].img || !(data->walls[4].img) || !(data->walls[5].img)))
    {
        printf("Error: assets\n");
		exit(2);
    }
}


int draw_map(t_data *data)
{
    int     i = 0;
    int     j = 0;

	mlx_destroy_image(data->mlx, data->img->img);
    data->img->img = mlx_new_image(data->mlx, data->wi, data->hi);
    data->img->addr = mlx_get_data_addr(data->img->img, &(data->img->bits_per_pixel), &(data->img->line_length), &(data->img->endian));
    if (data->flag == 0)
        init_player(data, data->map->p, (data->map->x - 1) * T_SIZE, (data->map->y - 1) * T_SIZE);
    data->flag = 1;
    player_movement(data);
    ray_casting(data);
    render_walls(data);
    mini_map(data);
// abdelbassat
    ft_sprit(data);
// abdelbassat
    /* draw_rays(data); */
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
    data->player->walk_dir = 0;
    data->player->turn_dir = 0;
	return (0);
}

void    open_door(t_data *data)
{
    int x;
    int y;

    y = data->player->py + ((4 * T_SIZE / 3) * sin(data->player->angle));
    x = data->player->px + ((4 * T_SIZE / 3) * cos(data->player->angle));
    if (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] == '2')
        data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] = '3';
    else if (data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] == '3')
        data->map->map[(int)(y / T_SIZE)][(int)(x / T_SIZE)] = '2';
}

int update_player(int key_code, t_data *data)
{
    int		x;
    int		y;
// abdelbassat
    if(key_code == 'f')
        data->flag_v1 = 1;
// abdelbassat
	if (key_code == LF_KEY)
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
        data->movement_flag = 1; 
        data->player->walk_dir = 1;
    }
    else if (key_code == ESC_KEY)
    {
        mlx_destroy_window(data->mlx, data->win);
        mlx_destroy_display(data->mlx);
        exit(1);
    }
	return (0); 
}

int main(int ac, char **av)
{
    t_data  data;
	char	*tmp1 = NULL;
    char    *s;
    int     i;
    void *img;
    t_map	map;

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
    data.row_len = data.map->x_win;
    data.column_len = data.map->y_win;
    data.wi = 1160;
	data.hi = 700;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, data.wi, data.hi, "window");
    data.img = malloc(sizeof(t_img));
    data.img->img = mlx_new_image(data.mlx, data.wi, data.hi);
    data.img->addr = mlx_get_data_addr(data.img->img, &(data.img->bits_per_pixel), &(data.img->line_length), &(data.img->endian));
    setup_testures(&data);
// abdelbassat
    ft_setup(&data);
// abdelbassat
	mlx_hook(data.win, 2, 1L<<0, &update_player, &data);
    mlx_loop_hook(data.mlx, draw_map , &data);
    mlx_loop(data.mlx);
}
