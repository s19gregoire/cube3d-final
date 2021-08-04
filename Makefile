# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneve <gneve@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/04 15:05:09 by gneve             #+#    #+#              #
#    Updated: 2021/08/04 15:06:07 by gneve            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = -L./mlx -lmlx -lXext -lX11 -lbsd -L./libft -lft -lm 

HEADER = -I./includes \

SRCS =  \
	    ./srcs/parser/parser.c \
    	./srcs/parser/parse_config.c \
		./srcs/parser/parse_config_utils.c \
    	./srcs/parser/parse_maze.c \
		./srcs/parser/parse_maze_utils.c \
		./srcs/parser/parse_check_walls.c \
		./srcs/parser/parser_utils.c \
		./srcs/raycaster/start_game.c \
		./srcs/raycaster/init_game.c \
		./srcs/raycaster/raycaster.c \
		./srcs/raycaster/raycaster_utils.c \
		./srcs/raycaster/textures.c \
		./srcs/utils/free.c \
		./srcs/utils/errors.c \
		./srcs/utils/colors.c \
		./srcs/utils/keys.c \
		./srcs/utils/movements.c \
		./srcs/main.c

SRCB = \
		./srcs/raycaster/sprites_bonus.c \
		./srcs/raycaster/2dmap_bonus.c

NBNS = -D BNS=0
BNS = -D BNS=1

OBJS = 	$(SRCS:.c=.o)
OBJB = 	$(SRCB:.c=.o)
MLX = ./mlx/libmlx.a
LIBFT = libft/libft.a

.c.o:
	$(CC) -g -Imlx -O2 -c $< -o $@

$(NAME): $(SRCS) $(LIBFT) $(MLX)
	$(CC) $(SRCS) $(CFLAGS) $(NBNS) $(LIB) $(HEADER) -o $(NAME)

all:$(NAME)
	
$(LIBFT):
	$(MAKE) -C ./libft

$(MLX):
	$(MAKE) -C ./mlx
		
bonus: $(SRCS) $(SRCB) $(LIBFT) $(MLX)
	$(CC) $(SRCS) $(SRCB) $(CFLAGS) $(BNS) $(LIB) $(HEADER) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJB)
	@cd libft && make clean
	@cd mlx && make clean

fclean:	clean
	@rm -rf $(NAME)
	@cd libft && make fclean

re:	fclean all

.PHONY:	all clean fclean re bonus
