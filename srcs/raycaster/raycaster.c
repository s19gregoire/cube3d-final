/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:11:54 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:11:55 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	get_walldistance(t_game *game)
{
	if (game->side.side == 0)
		game->wall.distance = (double)(game->side.mapx - game->player.posx
				+ (1 - game->side.stepx) / 2) / game->player.dirx;
	else
		game->wall.distance = (double)(game->side.mapy - game->player.posy
				+ (1 - game->side.stepy) / 2) / game->player.diry;
	game->wall.height = (int)(game->winH / game->wall.distance);
	game->wall.start = -game->wall.height / 2 + game->winH / 2;
	if (game->wall.start >= game->winW || game->wall.start < 0)
		game->wall.start = 0;
	game->wall.end = game->wall.height / 2 + game->winH / 2;
	if (game->wall.end >= game->winH || game->wall.end < 0)
		game->wall.end = game->winH - game->wall.start;
}

static int	detect_wall(t_game *game)
{
	if (game->side.x < game->side.y)
	{
		game->side.x += game->side.deltax;
		game->side.mapx += game->side.stepx;
		game->side.side = 0;
	}
	else
	{
		game->side.y += game->side.deltay;
		game->side.mapy += game->side.stepy;
		game->side.side = 1;
	}
	if (game->config.maze[game->side.mapx][game->side.mapy] == '1')
		return (1);
	return (0);
}

static void	get_side(t_game *game)
{
	if (game->player.dirx < 0)
	{
		game->side.stepx = -1;
		game->side.x = (game->player.posx - game->side.mapx)
			* game->side.deltax;
	}
	else
	{
		game->side.stepx = 1;
		game->side.x = (game->side.mapx + 1.0 - game->player.posx)
			* game->side.deltax;
	}
	if (game->player.diry < 0)
	{
		game->side.stepy = -1;
		game->side.y = (game->player.posy - game->side.mapy)
			* game->side.deltay;
	}
	else
	{
		game->side.stepy = 1;
		game->side.y = (game->side.mapy + 1.0 - game->player.posy)
			* game->side.deltay;
	}
}

static void	init_3d(t_game *game, int i)
{
	game->side.mapx = game->player.posx;
	game->side.mapy = game->player.posy;
	game->side.camx = (double)2 * i / game->winW - 1;
	game->player.dirx = game->player.initx + game->player.planex
		* game->side.camx;
	game->player.diry = game->player.inity + game->player.planey
		* game->side.camx;
	game->side.deltax = get_delta(game->player.diry, game->player.dirx);
	game->side.deltay = get_delta(game->player.dirx, game->player.diry);
}

void	draw_3d(t_game *game)
{
	int		i;
	int		hit;

	i = -1;
	while (++i < game->winW)
	{
		hit = 0;
		init_3d(game, i);
		get_side(game);
		while (!hit)
			hit = detect_wall(game);
		get_walldistance(game);
		draw_wall(i, game);
		if (BNS)
			game->zbuf[i] = game->wall.distance;
	}
	if (BNS)
		ft_sprites(game);
}
