CFLAGS = -g3 #-Wall -Wextra -Werror
XFLAGS = -lXext -lX11 -lm
SRCS = parse_map.c cub3d.c minimap.c ft_animation.c #libft/ft_strlen.c libft/ft_strchr.c libft/ft_strjoin.c libft/ft_strdup.c #get_next_line/get_next_line.c 
HEADERS = cub3d.h libft/libft.h #get_next_line/get_next_line.h
OBJS = $(SRCS:.c=.o)

LIBX = minilibx-linux/libmlx.a
LIBFT = libft/libft.a
NAME = cub3D

all : $(NAME)

.c.o : 
	cc -c $(CFLAGS) -o $@ $^

$(NAME) : $(OBJS) $(HEADERS) $(LIBX) $(LIBFT)
	cc  $(CFLAGS) $(XFLAGS) $(OBJS) $(LIBX) $(LIBFT) -o $(NAME)

$(LIBX) :
	$(MAKE) -C minilibx-linux
$(LIBFT) :
	$(MAKE) -C libft

clean :
	rm -f $(OBJS)
	$(MAKE) clean -C libft
fclean : clean 
	rm -f $(NAME)
	$(MAKE) clean -C minilibx-linux
	$(MAKE) fclean -C libft
re : fclean all