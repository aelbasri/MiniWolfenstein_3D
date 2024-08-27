CFLAGS = -g3 -Wall -Wextra -Werror# -fsanitize=address
XFLAGS = -lXext -lX11 -lm
SRCS = $(addprefix ./src/, cub3d.c cub3d_utils.c minimap.c  movement/player_movement.c movement/player_movement_utils.c rendering/ft_animation.c rendering/rendering.c raycaster/raycasting.c rendering/rendering_utils.c raycaster/raycasting_utilse.c parse/utils_parse1.c parse/utils_parse2.c parse/utils_parse.c parse/parse_map.c)#parse_map.c cub3d.c minimap.c #libft/ft_strlen.c libft/ft_strchr.c libft/ft_strjoin.c libft/ft_strdup.c #get_next_line/get_next_line.c 
HEADERS = include/cub3d.h utils/libft/libft.h 
OBJS = $(SRCS:.c=.o)

LIBX = utils/minilibx-linux/libmlx.a
LIBFT = utils/libft/libft.a
NAME = cub3D

all : $(NAME)

.c.o : 
	cc -c $(CFLAGS) -o $@ $^

$(NAME) : $(OBJS) $(HEADERS) $(LIBX) $(LIBFT)
	cc  $(CFLAGS) $(XFLAGS) $(OBJS) $(LIBX)  $(LIBFT) -o $(NAME)

$(LIBX) :
	$(MAKE) -C utils/minilibx-linux
$(LIBFT) :
	make bonus -C utils/libft
	$(MAKE) -C utils/libft

clean :
	rm -f $(OBJS)
	$(MAKE) clean -C utils/libft
fclean : clean 
	rm -f $(NAME)
	$(MAKE) clean -C utils/minilibx-linux
	$(MAKE) fclean -C utils/libft
re : fclean all