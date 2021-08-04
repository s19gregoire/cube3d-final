/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:54:06 by mlazzare          #+#    #+#             */
/*   Updated: 2021/06/11 07:32:42 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "structs.h"
# include "../mlx/mlx.h"

# ifndef BNS
#  define BNS 0
# endif

# define PI 3.14159265359
# define PLAYER 3
# define OFFSET 0
# define STEP 5
# define SPEED 0.05
# define ROT 0.05
# define FOV 1
# define SCREENW 1000
# define SCREENH 800
# define TILE 5
# define RAY 20
# define FILESIZE 1000

# define BLACK -16777216
# define GRAY 0xC0C0C0
# define PURPLE 0x7d0330
# define RED 0xFF0000
# define GREEN 0x037d50
# define YELLOW 0xFFFF00

# define UP_KEY 65362
# define DOWN_KEY 65364
# define RIGHT_KEY 65363
# define LEFT_KEY 65361
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define Q_KEY 12
# define ESC_KEY 65307

/*
* PARSER
*/

int		read_map(t_map *map, char **av);
int		get_path(t_map *map, char *line);
int		get_sprite_path(t_map *map, char *line);
int		get_rgb_value(t_map *map, int *s, char *line);
int		get_maze(t_map *map);
int		get_error(char c);
int		get_startwall(t_map *map, char *l, int y);
int		get_endwall(t_map *map, char *l);
int		get_playerpos(t_map *map, int y);
int		ft_ismaze(char c);
int		ft_isplayerpos(char c);
int		ft_isdirection(char *li, int i);
int		ft_issprite(char a, char b);
int		skip_space(char *l, int i);
int		check_cf(char *line);
int		not_walled(int pos, t_map *map);
int		check_spaces(int pos, t_map *map, char *l);
int		check_emptyline(char *line, t_map *map);
int		check_maze(t_map *map, char *l, int y);
int		check_top_wall(t_map *map);
int		check_walls(t_map *map, char *l);
int		check_bottom_wall(t_map *map, char *l);
int		check_side_walls(t_map *map, char *l);
int		check_if_walled(t_map *map, char *l);
int		map_checked(t_map *map);
int		check_map(t_map *map, int err);
int		fill_map(t_map *map, int err);
int		check_line(int err, int space, t_map *map);
int		free_line(char *l);
int		check_err(int err, int space, t_map *map);
void	free_parse(t_map *map);
char	*trimspaces(char *s);
int		start_game(t_map map);
int		init_game(t_game *game, t_map map);
int		draw_2dmap(t_game *game);
int		texture_to_img(t_game *game);
int		draw_texture(t_game *game, int x, int y);
int		get_colors(t_map *map, char c);
void	draw_pixel(t_game *game, int y, int x, int color);
void	draw_wall(int i, t_game *game);
void	rotate_view(t_game *game, double dx, double px);
void	move_backforwards(t_game *game);
void	move_leftright(t_game *game);
void	draw_3d(t_game *game);
void	get_orientation(t_game *game);
void	ft_sprites(t_game *game);
int		x_exit(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
double	get_delta(double dir1, double dir2);
void	draw_spriteline(t_game *game, int i, int s);
void	free_map(t_map *map);
int		free_window(t_game *game);
void	free_game(t_game *game);
int		free_dataimg(t_game *game);

#endif
