#include "cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

void line(t_data *data, double len, int color)
{
    double steps;
    double x = data->player->px;
    double y = data->player->py;
    double i = 0;
    t_line  line;

    line.x2 = (data->player->px) + (len * cos(data->player->angle));  
    line.y2 = (data->player->py) + (len * sin(data->player->angle));  
    line.xs = line.x2 - data->player->px;
    line.ys = line.y2 - data->player->py;
    steps = fmax(fabs(line.xs),fabs(line.ys));
    line.xi = line.xs / steps;
    line.yi = line.ys / steps;

    while (i <= steps && (x >= 0 && x < data->row_len * 16) && ((y >= 0 && y < data->column_len * 16)))
    {
		my_mlx_pixel_put(data->img, x, y, color);
        x = x + line.xi;
        y = y + line.yi;
        i++;
    }
}

void normalize(double *angle)
{
    *angle = fmod(*angle , (2 * M_PI));
    if (*angle < 0)
        *angle += 2 * M_PI;
}

void line_2(t_data *data, double xx, double yy, int color, double angle)
{

    double steps;
    double len = sqrt((pow(data->player->px - xx, 2) + pow(data->player->py - yy, 2)));
    double x = data->player->px;
    double y = data->player->py;
    double i = 0;
    t_line  line;

    line.x2 = (data->player->px) + (len * cos(angle));  
    line.y2 = (data->player->py) + (len * sin(angle));  
    line.xs = line.x2 - data->player->px;
    line.ys = line.y2 - data->player->py;
    steps = fmax(fabs(line.xs),fabs(line.ys));
    line.xi = line.xs / steps;
    line.yi = line.ys / steps;

    while (i <= steps && (x >= 0 && x < data->row_len * 16) && ((y >= 0 && y < data->column_len * 16)))
    {
		my_mlx_pixel_put(data->img, x, y, color);
        x = x + line.xi;
        y = y + line.yi;
        i++;
    }
}

void    draw_rays(t_data *data)
{
    t_ray *tmp;
    int i = 0;

    tmp = data->ray;
    while (tmp != NULL)
    {
        line_2(data, tmp->x, tmp->y, 0xFF00000, tmp->angle);
        tmp = tmp->next;
    }
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
        y_init = ((int)(data->player->py / 16.0)) + 1;
        y_max = ((int)(data->column_len));
    }
    else
    {
        y_init = ((int)(data->player->py / 16.0));
        y_max = 0;
        j = -1;
        i = -1;
    }
    while (y_max - (j * y_init) >= 0)
	{
		ray->x = data->player->px + ((((double)(y_init * 16)) - data->player->py) / tan(angle));
        if (ray->x < 0)
            ray->x = 0;
        if (ray->x > (data->row_len - 1) * 16)
            ray->x = (data->row_len - 1) * 16;
		if (y_init + i >= data->column_len || data->map->map[y_init + i][(int)ray->x / 16] == '1')
			break;
        y_init += j; 
    }
    if ((angle >= 0 && angle <= M_PI / 2) || (angle >= 3 * M_PI / 2 &&  angle <= 2 * M_PI))
    {
        j = 1;
        i = 0;
        x_init = ((int)(data->player->px / 16.0)) + 1;
        x_max = (int)(data->row_len);
    }
    else
    {
        x_init = ((int)(data->player->px / 16.0));
        x_max = 0;
        j = -1;
        i = -1;
    }
	while (x_max - (x_init * j) >= 0)
	{
		ray->y = data->player->py + ((((double)(x_init * 16)) - data->player->px) * tan(angle));
        if (ray->y < 0)
            ray->y = 0;
        if (ray->y > (data->column_len - 1) * 16)
            ray->y = (data->column_len - 1) * 16;
        if (x_init + i >= data->row_len || data->map->map[(int)ray->y / 16][x_init + i] == '1')
			break;
        x_init += j;
	}
    /* √((x1 - x)² + (y1 - y)²) < √((x1 - x)² + (y1 - y)²) */
	if (sqrt((pow(ray->x - data->player->px, 2) + pow((double)(y_init * 16.0) - data->player->py, 2))) <
		sqrt((pow(data->player->px - (double)(x_init * 16.0), 2) + pow(data->player->py - ray->y, 2))))
    	ray->y = (double)(y_init * 16.0);
    else
		ray->x = (double)(x_init * 16.0);
    ray->angle = angle;
    ray->next = NULL;
    return (ray);
}

void    one_wall_rendering(t_data *data, int j, t_ray *ray)
{
	double	distance;
    double  wall_height;
    double  a;
    int     i;
	
    i = 0;
	distance = sqrt((pow(data->player->px - ray->x, 2) + pow(data->player->py - ray->y, 2))) * cos(data->player->angle - ray->angle);
    wall_height =(data->hi * 16) / distance;
    a = (data->hi - wall_height) / 2;
        i = 0;
        while (i <= data->hi)
        {
            if (i >= 0 && i <= a)
                my_mlx_pixel_put(data->img, j, i, data->map->C);
            else if (i > a && i <= a + wall_height)
                my_mlx_pixel_put(data->img, j, i, 0x00000000);
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

void player_movement(t_data *data)
{
    double	x;
    double	y;


    normalize(&(data->player->angle));
	y = data->player->py + (sin(data->player->angle) * (data->player->walk_dir));
	x = data->player->px + (cos(data->player->angle) * (data->player->walk_dir));
	if (data->map->map[(int)(y / 16.0)][(int)(x / 16.0)] != '1')
    {
		data->player->py += sin(data->player->angle) * (data->player->walk_dir);
		data->player->px += cos(data->player->angle) * (data->player->walk_dir);
    }
}

int	init_player(t_data *data, double angle, int x, int y)
{
	data->player = malloc(sizeof(t_player));
	data->player->angle = angle;
	data->player->walk_dir = 0;
	data->player->turn_dir = 0;
	data->player->px = x + 8;
	data->player->py = y + 8;
    data->player->p_speed = 3;
	return (0);
}

void    mini_map(t_data *data)
{
	int		i = 0;
    int     j = 0;

	while(j < data->column_len)
	{
        i = 0;
        while(i < data->row_len)
        {
            if (data->map->map[j][i] == '1')
                put_square(data, i * 16, j * 16, 16, 0xffffffff);
            else
                put_square(data, i * 16, j * 16, 16, 0x00000000);
            i++;
        }
        j++;
    }
    put_square(data, data->player->px - 2.0, data->player->py - 2.0, 4.0, 0xFF00000);
    line(data, 16, 0xFF00000);
    // draw_rays(data);
}

int draw_map(t_data *data)
{
    int     i = 0;
    int     j = 0;

	mlx_destroy_image(data->mlx, data->img->img);
    data->img->img = mlx_new_image(data->mlx, data->wi, data->hi);
    data->img->addr = mlx_get_data_addr(data->img->img, &(data->img->bits_per_pixel), &(data->img->line_length), &(data->img->endian));
    if (data->flag == 0)
        init_player(data, E, (data->map->x - 1) * 16, (data->map->y - 1) * 16);
    data->flag = 1;
    player_movement(data);
    ray_casting(data);
    render_walls(data);
    mini_map(data);
    // draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img, 0, 0);
    data->player->walk_dir = 0;
    data->player->turn_dir = 0;
	return (0);
}

int update_player(int key_code, t_data *data)
{
	if (key_code == LF_KEY)
		data->player->angle = data->player->angle - (2 * (M_PI / 180));
    else if (key_code == RT_KEY)
		data->player->angle = data->player->angle + (2 * (M_PI / 180));
    else if (key_code == S_KEY)
        data->player->walk_dir = -1;
    // else if (key_code == A_KEY)
    // {
    //     if (data->player->px > 0)
    //         data->player->px -= 1;
    // }
    else if (key_code == W_KEY)
        data->player->walk_dir = 1;
    // else if (key_code == D_KEY)
    // {
    //     if (data->player->px < (data->row_len * 16) - 16)
    //         data->player->px += 1;
    // }
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
	mlx_hook(data.win, 2, 1L<<0, &update_player, &data);
    mlx_loop_hook(data.mlx, draw_map , &data);
    mlx_loop(data.mlx);
}