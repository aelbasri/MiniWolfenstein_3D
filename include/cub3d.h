/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:32:29 by aelbasri          #+#    #+#             */
/*   Updated: 2024/08/27 14:48:53 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define S_WALL 256

# include "../utils/libft/libft.h"
# include "../utils/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define VERTICAL 1
# define HORIZONTAL 0

# define MINI_X 14
# define MINI_Y 6

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

# define UP_KEY 65362
# define DN_KEY 65364
# define LF_KEY 65361
# define RT_KEY 65363
# define ESC_KEY 65307
# define T_SIZE 32

# define M_PI 3.14159265358979323846
# define F_VIEW 1.0471975512
# define E 0.0
# define S 1.57079632679
# define W M_PI
# define N 4.71238898038

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				endian;
	int				line_length;
	int				bits_per_pixel;
}					t_img;

typedef struct s_ray_cast
{
	int				x_init;
	int				x_max;
	int				j;
	int				i;
	int				y_init;
	int				y_max;
}					t_ray_cast;

typedef struct s_render
{
	double			distance;
	unsigned int	color;
	double			wall_height;
	double			wall_width;
	double			a;
	int				b;
	double			x;
	double			y;
	int				i;
}					t_render;

typedef struct s_ray
{
	double			x;
	double			y;
	int				inter_d;
	double			angle;
	struct s_ray	*next;
}					t_ray;

typedef struct s_player
{
	double			px;
	double			py;
	double			walk_dir;
	double			turn_dir;
	double			angle;
	double			p_speed;
	double			rotation_speed;
}					t_player;

typedef struct s_line
{
	double			xs;
	double			ys;
	double			xi;
	double			yi;
	double			x2;
	double			y2;
}					t_line;

typedef struct s_map
{
	int				f;
	int				c;
	int				x;
	int				y;
	int				x_win;
	int				y_win;
	char			p;
	char			**map;
	char			*so;
	char			*ea;
	char			*we;
	char			*no;

}					t_map;

typedef struct s_data
{
	int				x;
	int				y;
	int				flag;
	int				movement_flag;
	double			steps;
	int				rays_nbr;
	int				row_len;
	int				column_len;
	int				wi;
	int				hi;
	int				flag_v1;
	void			*mlx;
	void			*win;
	int				fd;
	double			angle;
	int				text_y;
	int				text_x;
	t_img			walls[6];
	t_ray			*ray;
	t_map			*map;
	t_img			*animation;
	t_img			*img;
	t_player		*player;
}					t_data;

int					ft_read_map(char *file, t_map *map);
void				put_square(t_data *data, int x, int y, int color);
void				mini_map(t_data *data);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
int					check_and_move(t_data *data, double angle);
void				player_movement(t_data *data);
int					update_player(int key_code, t_data *data);
t_ray				*ray_create(t_data *data, double angle);
void				ray_casting(t_data *data);
void				check_direction_horizontal(t_ray_cast *cast, t_data *data,
						double angle);
void				check_direction_vertical(t_ray_cast *cast, t_data *data,
						double angle);
void				get_intersections_horizontal(t_ray_cast *cast, t_ray *ray,
						t_data *data, double angle);
void				get_intersections_vertical(t_ray_cast *cast, t_ray *ray,
						t_data *data, double angle);
void				get_x(int *b, double *x, t_ray *ray, t_data *data);
unsigned int		get_color(t_data *data, t_render render);
void				one_wall_rendering(t_data *data, int j, t_ray *ray);
void				mouse_movement(t_data *data);
void				render_walls(t_data *data);
void				setup_testures(t_data *data);
int					draw_map(t_data *data);
void				normalize(double *angle);
int					init_player(t_data *data, char angle, int x, int y);
void				open_door(t_data *data);
void				ft_exit(t_data *data);
void				init(t_data *data);
void				move_2(t_data *data);
void				move_1(t_data *data);
int					check_valid_position(t_data *data, int x, int y);
int					check_and_move(t_data *data, double angle);
int					my_mlx_pixel_put_v1(t_img *data, int x, int y);
void				ft_setup(t_data *data);
void				ft_sprit(t_data *data);
int					ft_path(char *str, t_map *map);
int					ft_check_char(char *str, t_map *map);
void				ft_check_num(char *num, int *color, int *count);
int					check_space(char **map, int i, int j);
char				*get_next_line(char *file);
char				*ft_join(char *str, int max);
int					chpath(char *file, char *ex);
int					ft_len_v1(char **str);
t_list				*ft_return(void);
void				*ft_malloc(size_t num);
void				ft_free(void);
char				*ft_return_num(char *num);
int					ft_strcmp(char *s1, char *s2);
#endif
