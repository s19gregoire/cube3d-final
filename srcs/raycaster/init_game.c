/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:11:19 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:11:24 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_singlesprite(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->config.sprites)
	{
		game->sprites[i].x = 0;
		game->sprites[i].y = 0;
		game->sprites[i].dist = 0;
		game->sprites[i].stx = 0;
		game->sprites[i].endx = 0;
		game->sprites[i].sty = 0;
		game->sprites[i].endy = 0;
		game->sprites[i].W = 0;
		game->sprites[i].H = 0;
		game->sprites[i].tx = 0;
		game->sprites[i].ty = 0;
		game->sprites[i].screenx = 0;
	}
}

static int	init_sprites(t_game *game)
{
	game->zbuf = malloc(sizeof(double) * game->winW);
	if (!game->zbuf)
		return (0);
	game->sprites = malloc(sizeof(t_sprite) * game->config.sprites);
	if (!game->sprites)
	{
		free(game->zbuf);
		return (0);
	}		
	init_singlesprite(game);
	return (1);
}

static void	init_texture(t_game *game)
{
	int	j;

	j = -1;
	while (++ j < 4)
	{
		game->tex[j].img = 0;
		game->tex[j].addr = 0;
		game->tex[j].height = 0;
		game->tex[j].width = 0;
	}
	game->t.dir = 0;
	game->t.wallx = 0;
	game->t.x = 0;
	game->t.y = 0;
	game->t.height = 0;
	game->t.width = 0;
	game->t.initpos = 0;
	game->t.step = 0;
	game->spritex.img = 0;
	game->spritex.addr = 0;
	game->spritex.height = 0;
	game->spritex.width = 0;
}

static void	init_wallside(t_game *game)
{
	game->wall.distance = 0;
	game->wall.height = 0;
	game->wall.start = 0;
	game->wall.end = 0;
	game->side.x = 0;
	game->side.y = 0;
	game->side.deltax = 0;
	game->side.deltay = 0;
	game->side.stepx = 0;
	game->side.stepy = 0;
	game->side.side = 0;
	game->side.camx = 0;
	game->side.mapx = 0;
	game->side.mapy = 0;
}

int	init_game(t_game *game, t_map map)
{
	game->config = map;
	game->winW = SCREENW;
	game->winH = SCREENH;
	game->player.posx = game->config.x + 0.5;
	game->player.posy = game->config.y + 0.5;
	game->player.dirx = -1;
	game->player.diry = 0;
	game->move.forw = 0;
	game->move.back = 0;
	game->move.right = 0;
	game->move.left = 0;
	game->move.rotright = 0;
	game->move.rotleft = 0;
	get_orientation(game);
	init_wallside(game);
	init_texture(game);
	if (BNS)
		return (init_sprites(game));
	return (1);
}
