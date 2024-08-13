#ifndef CUB3D_H
# define CUB3D_H

# define S_WALL 32

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# define VERTICAL 1
# define HORIZONTAL 0

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

#define M_PI 3.14159265358979323846
#define F_VIEW M_PI / 3
#define E 0.0
#define S M_PI / 2
#define W M_PI
#define N 3 * M_PI / 2

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		endian;
    int		line_length;
	int		bits_per_pixel;
} t_img;

typedef struct s_ray
{
	double	x;
	double	y;
	int		inter_d;
	double	angle;
	struct s_ray *next;
} t_ray;

typedef struct s_player
{
	double		px;
	double		py;
	double		walk_dir;   // +1 front, -1 back 
	double		turn_dir;	// +1 right, -1 left
	double	 	angle;
	double		p_speed;
	double		rotation_speed;
} t_player;

typedef struct s_line
{
	double xs;
    double ys;
    double xi;
    double yi;
    double x2;
    double y2;
} t_line;

typedef struct s_map
{
	int			F;
	int			C;
	int			x;
	int			y;
	int			x_win;
	int			y_win;
	char p;
	char		**map;
	char		*so;
	char		*ea;
	char		*we;
	char		*no;

}				t_map;

typedef struct s_data
{
	int		flag;
    double  steps;
	int		rays_nbr;
	int		row_len;
	int		column_len;
	int		wi;
	int		hi;
	double	xx;
	double	yy;
	double	zz;
	void    *mlx;
    void    *win;
	int     fd;
	int		text_y;
	int		text_x;
	t_img	walls[4];
	t_ray	*ray;
	t_map	*map;
	t_img	*img;
    t_player   *player;
} t_data;

int	ft_Read_Map(char *file, t_map *map);

#endif