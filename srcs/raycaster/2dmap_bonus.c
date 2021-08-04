/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2dmap_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:10:56 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:10:58 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_mapsprite(int x, int y, t_game *game, int color)
{
	int	dx;
	int	dy;

	dy = -1 + TILE / 3;
	while (++dy < TILE / 3 * 2)
	{
		dx = -1 + TILE / 3;
		while (++dx < TILE / 3 * 2)
			draw_pixel(game, (int)(dy + y), (int)(dx + x), color);
	}
}

static void	draw_player(t_game *game)
{
	int	dx;
	int	dy;
	int	pixel;

	dy = -1;
	while (++dy < PLAYER)
	{
		dx = -1;
		while (++dx < PLAYER)
		{
			pixel = game->winW * (int)(dy + game->player.posx * TILE)
				+ (int)(dx + game->player.posy * TILE);
			if (!(game->img.addr[pixel] == GRAY
					|| game->img.addr[pixel] == PURPLE))
				draw_pixel(game, (int)(dy + game->player.posx * TILE),
					(int)(dx + game->player.posy * TILE), YELLOW);
		}
	}	
}

static void	draw_ray(t_game *game, double px, double py)
{
	double	dx;
	double	dy;
	int		pixel;
	int		i;

	i = -1;
	dx = game->player.planex;
	dy = -game->player.planey;
	while (++i < RAY)
	{
		pixel = (int)(game->winW * floor(px + dy) + floor(py + dx));
		if (pixel < 0 || floor(px + dy) > game->winW
			|| floor(py + dx) > game->winH
			|| game->img.addr[pixel] == GRAY || game->img.addr[pixel] == PURPLE)
			break ;
		if (game->img.addr[pixel] == GREEN)
			draw_pixel(game, (int)floor(px + dy), (int)floor(py + dx), RED);
		dx += game->player.planex;
		dy += -game->player.planey;
	}
}

static void	draw_tile(int x, int y, t_game *game, int color)
{
	int	dx;
	int	dy;

	dy = -1;
	while (++dy < TILE)
	{
		dx = -1;
		while (++dx < TILE)
			draw_pixel(game, (int)(dy + y), (int)(dx + x), color);
	}
}

int	draw_2dmap(t_game *game)
{
	int	x;
	int	y;

	y = -1;
	while (game->config.maze[++y])
	{
		x = -1;
		while (game->config.maze[y][++x])
		{
			if (game->config.maze[y][x] == '1')
				draw_tile(x * TILE, y * TILE, game, GRAY);
			else if (game->config.maze[y][x] != ' ')
				draw_tile(x * TILE, y * TILE, game, GREEN);
			if (game->config.maze[y][x] == '2')
				draw_mapsprite(x * TILE, y * TILE, game, PURPLE);
		}
	}
	draw_player(game);
	draw_ray(game, PLAYER / 2 + TILE * game->player.posx,
		PLAYER / 2 + TILE * game->player.posy);
	return (0);
}
