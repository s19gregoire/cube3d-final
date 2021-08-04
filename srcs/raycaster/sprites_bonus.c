/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:12:04 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:12:06 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	sprite_endstart(t_game *game, int i)
{
	if (game->sprites[i].sty < 0)
		game->sprites[i].sty = 0;
	game->sprites[i].endy = game->sprites[i].H / 2 + game->winH / 2;
	if (game->sprites[i].endy >= game->winH)
		game->sprites[i].endy = game->winH - 1;
	game->sprites[i].W = abs((int)(game->winH / game->sprites[i].ty));
	game->sprites[i].stx = -game->sprites[i].W / 2 + game->sprites[i].screenx;
	if (game->sprites[i].stx < 0)
		game->sprites[i].stx = 0;
	game->sprites[i].endx = game->sprites[i].W / 2 + game->sprites[i].screenx;
	if (game->sprites[i].endx >= game->winW)
		game->sprites[i].endx = game->winW - 1;
}

static void	draw_sprite(t_game *game, int s)
{
	int		i;

	sprite_endstart(game, s);
	i = game->sprites[s].stx - 1;
	while (++i < game->sprites[s].endx)
		draw_spriteline(game, i, s);
}

static void	get_spritepos(t_game *game)
{
	int		i;
	int		y;
	int		x;

	x = -1;
	i = 0;
	while (game->config.maze[++x])
	{
		y = -1;
		while (game->config.maze[x][++y])
		{
			if (game->config.maze[x][y] == '2')
			{
				game->sprites[i].x = x + 0.5;
				game->sprites[i].y = y + 0.5;
				game->sprites[i].dist = (game->player.posx - game->sprites[i].x)
					* (game->player.posx - game->sprites[i].x)
					+ (game->player.posy - game->sprites[i].y)
					* (game->player.posy - game->sprites[i].y);
				i++;
			}
		}
	}
}

static void	sort_sprites(t_game *game, int num)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = -1;
	while (++i < num)
	{
		j = -1;
		while (++j < num - 1)
		{
			if (game->sprites[j + 1].dist > game->sprites[j].dist)
			{
				tmp = game->sprites[j];
				game->sprites[j] = game->sprites[j + 1];
				game->sprites[j + 1] = tmp;
			}
		}
	}
}

void	ft_sprites(t_game *game)
{
	int			i;
	double		sx;
	double		sy;
	double		inv;

	get_spritepos(game);
	sort_sprites(game, game->config.sprites);
	i = -1;
	while (++i < game->config.sprites)
	{
		sx = game->sprites[i].x - game->player.posx;
		sy = game->sprites[i].y - game->player.posy;
		inv = 1.0 / (game->player.planex * game->player.inity
				- game->player.initx * game->player.planey);
		game->sprites[i].tx = inv * (game->player.inity * sx
				- game->player.initx * sy);
		game->sprites[i].ty = inv * (-game->player.planey * sx
				+ game->player.planex * sy);
		game->sprites[i].screenx = game->winW / 2
			* (1 + game->sprites[i].tx / game->sprites[i].ty);
		game->sprites[i].H = abs((int)(game->winH
					/ game->sprites[i].ty));
		game->sprites[i].sty = -game->sprites[i].H / 2 + game->winH / 2;
		draw_sprite(game, i);
	}
}
