/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 11:26:17 by mlazzare          #+#    #+#             */
/*   Updated: 2021/06/06 18:40:00 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_map
{
	char		*no;
	char		*so;
	char	 	*we;
	char	 	*ea;
	char	 	*s;
	char		**maze;
	char		*line;
	char		*trim;
	int	 		idx;
	int			x;
	int			y;
	int			start_wall;
	int			end_wall;
	int	 		sprites;
	int			f_check;
	int			c_check;
	int			complete;
	int			end;
	int			f[3];
	int			c[3];
}				t_map;

typedef struct s_data
{
	void		*img;
	int			*addr;
	void		*img2;
	int			*addr2;	
	int			counter;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_moves
{
	int			forw;
	int			back;
	int			left;
	int			right;
	int			rotleft;
	int			rotright;
}				t_moves;

typedef struct s_tex
{
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			height;
	int			width;
}				t_tex;

typedef struct s_sprite
{
	double		x;
	double		y;
	double		dist;
	int			stx;
	int			endx;
	int			sty;
	int			endy;
	int			W;
	int			H;
	double		tx;
	double		ty;
	int			screenx;
}				t_sprite;

typedef struct s_texparam
{
	int			dir;
	double		wallx;
	int			x;
	int			y;
	int			height;
	int			width;
	double		initpos;
	double		step;
}				t_texparam;

typedef struct s_vec
{
	double		x;
	double		y;
	double		deltax;
	double		deltay;
	int			stepx;
	int			stepy;
	int			side;
	double		camx;
	int			mapx;
	int			mapy;
}				t_vec;

typedef struct s_ray
{
	double		angle;
	double		posx;
	double		posy;
	double		planex;
	double		planey;
	double		dirx;
	double		diry;
	double		initx;
	double		inity;
	double		speed;
}				t_ray;

typedef struct s_wall
{
	double		distance;
	int			height;
	int			start;
	int			end;
}				t_wall;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	double		*zbuf;
	int			winW;
	int			winH;
	t_sprite	*sprites;
	t_data		img;
	t_tex		tex[5];
	t_tex		spritex;
	t_texparam	t;
	t_map		config;
	t_vec		side;
	t_moves		move;
	t_ray		player;
	t_wall		wall;
}				t_game;

#	endif
