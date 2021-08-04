/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:11:42 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:11:44 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_wall(int i, t_game *game)
{
	int	j;

	j = -1;
	while (++j < game->wall.start)
		game->img.addr[j * game->img.line_length / 4 + i]
			= get_colors(&game->config, 'c');
	j = draw_texture(game, i, j);
	while (++j <= game->winH)
		game->img.addr[j * game->img.line_length / 4 + i]
			= get_colors(&game->config, 'f');
}

void	draw_spriteline(t_game *game, int i, int s)
{
	int	y;
	int	tex;
	int	tey;
	int	d;

	y = game->sprites[s].sty - 1;
	tex = (int)(256 * (i - (-game->sprites[s].W / 2
					+ game->sprites[s].screenx))
			* game->spritex.width / game->sprites[s].W) / 256;
	if (game->sprites[s].ty > 0 && i > 0 && i < game->winW
		&& game->sprites[s].ty < game->zbuf[i])
	{
		while (++y < game->sprites[s].endy)
		{
			d = (int)(y * 256 - game->winH
					* 128 + game->sprites[s].H * 128);
			tey = ((d * game->spritex.height)
					/ game->sprites[s].H) / 256;
			if (game->spritex.addr[tey * game->spritex.line_length / 4 + tex]
				!= BLACK)
				game->img.addr[y * game->img.line_length / 4 + i]
					= game->spritex.addr[tey
					* game->spritex.line_length / 4 + tex];
		}
	}
}

double	get_delta(double dir1, double dir2)
{
	if (dir1 == 0)
		return (0);
	else if (dir2 == 0)
		return (1);
	return (fabs(1 / dir2));
}

static void	update_orientation(t_game *game)
{
	char	p;

	p = game->config.maze[game->config.x][game->config.y];
	if (p == 'N' || p == 'S')
	{
		game->player.inity = 0;
		game->player.planex = 0;
	}
	else
	{
		game->player.initx = 0;
		game->player.planey = 0;
	}
	game->config.maze[game->config.x][game->config.y] = '0';
}

void	get_orientation(t_game *game)
{
	char	p;

	p = game->config.maze[game->config.x][game->config.y];
	if (p == 'N')
	{
		game->player.initx = -FOV;
		game->player.planey = 0.66;
	}
	else if (p == 'S')
	{
		game->player.initx = FOV;
		game->player.planey = -0.66;
	}
	else if (p == 'E')
	{
		game->player.inity = FOV;
		game->player.planex = 0.66;
	}
	else if (p == 'W')
	{
		game->player.inity = -FOV;
		game->player.planex = -0.66;
	}
	update_orientation(game);
}
