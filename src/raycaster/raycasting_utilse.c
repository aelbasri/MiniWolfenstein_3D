#include "../../include/cub3d.h"

void    check_direction_horizontal(t_ray_cast *cast, t_data *data, double angle)
{
    if (angle >= 0 && angle <= M_PI)
    {
        cast->j = 1;
        cast->i = 0;
        cast->y_init = ((int)(data->player->py / T_SIZE)) + 1;
        cast->y_max = ((int)(data->column_len));
    }
    else
    {
        cast->y_init = ((int)(data->player->py / T_SIZE));
        cast->y_max = 0;
        cast->j = -1;
        cast->i = -1;
    }
}

void    check_direction_vertical(t_ray_cast *cast, t_data *data, double angle)
{
    if ((angle >= 0 && angle <= M_PI / 2) || (angle >= 3 * M_PI / 2 &&  angle <= 2 * M_PI))
    {
        cast->j = 1;
        cast->i = 0;
        cast->x_init = ((int)(data->player->px / T_SIZE)) + 1;
        cast->x_max = (int)(data->row_len);
    }
    else
    {
        cast->x_init = ((int)(data->player->px / T_SIZE));
        cast->x_max = 0;
        cast->j = -1;
        cast->i = -1;
    }
}
void    get_intersections_horizontal(t_ray_cast *cast, t_ray *ray, t_data *data, double angle)
{
    while (cast->y_max - (cast->j * cast->y_init) >= 0)
	{
		ray->x = data->player->px + ((((double)(cast->y_init * T_SIZE)) - data->player->py) / tan(angle));
        if (ray->x < 0)
            ray->x = 0;
        if (ray->x > (data->row_len - 1) * T_SIZE)
            ray->x = (data->row_len - 1) * T_SIZE;
		if (cast->y_init + cast->i < 0 || cast->y_init + cast->i >= data->column_len || \
        data->map->map[cast->y_init + cast->i][(int)ray->x / T_SIZE] == '1' || \
        data->map->map[cast->y_init + cast->i][(int)ray->x / T_SIZE] == '2')
			break;
        cast->y_init += cast->j; 
    }
}

void    get_intersections_vertical(t_ray_cast *cast, t_ray *ray, t_data *data, double angle)
{
    while (cast->x_max - (cast->x_init * cast->j) >= 0)
	{
		ray->y = data->player->py + ((((double)(cast->x_init * T_SIZE)) - data->player->px) * tan(angle));
        if (ray->y < 0)
            ray->y = 0;
        if (ray->y > (data->column_len - 1) * T_SIZE)
            ray->y = (data->column_len - 1) * T_SIZE;
        if (cast->x_init + cast->i < 0 || cast->x_init + cast->i >= data->row_len || \
        data->map->map[(int)ray->y / T_SIZE][cast->x_init + cast->i] == '1' || 
        data->map->map[(int)ray->y / T_SIZE][cast->x_init + cast->i] == '2')
			break;
        cast->x_init += cast->j;
	}
}