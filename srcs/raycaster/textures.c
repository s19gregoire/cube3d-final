/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:12:29 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:12:33 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	texture_direction(t_game *game)
{
	if (game->side.side == 0 && game->player.dirx < 0)
		game->t.dir = 0;
	if (game->side.side == 0 && game->player.dirx >= 0)
		game->t.dir = 1;
	if (game->side.side == 1 && game->player.diry < 0)
		game->t.dir = 2;
	if (game->side.side == 1 && game->player.diry >= 0)
		game->t.dir = 3;
	if (game->side.side == 0)
		game->t.wallx = game->player.posy + game->wall.distance
			* game->player.diry;
	else
		game->t.wallx = game->player.posx + game->wall.distance
			* game->player.dirx;
	game->t.wallx -= floor((game->t.wallx));
}

int	draw_texture(t_game *game, int x, int y)
{
	int	pixel;

	texture_direction(game);
	game->t.step = 1.0 * game->tex[game->t.dir].height / game->wall.height;
	game->t.x = (int)(game->t.wallx * game->tex[game->t.dir].width);
	if ((game->side.side == 0 && game->player.dirx > 0)
		|| (game->side.side == 1 && game->player.diry < 0))
		game->t.x = game->tex[game->t.dir].width - game->t.x - 1;
	game->t.initpos = (game->wall.start - game->winH / 2
			+ game->wall.height / 2) * game->t.step;
	while (y <= game->wall.end)
	{
		game->t.y = (int)game->t.initpos & (game->tex[game->t.dir].height - 1);
		game->t.initpos += game->t.step;
		pixel = (int)y * game->img.line_length / 4 + x;
		if (y < game->winH && x < game->winW)
			game->img.addr[pixel] = game->tex[game->t.dir].addr[game->t.y
				* game->tex[game->t.dir].line_length / 4 + game->t.x];
		y++;
	}
	return (y - 1);
}

static int	sprite_texture(t_game *game)
{
	game->spritex.img = mlx_xpm_file_to_image(game->mlx,
			game->config.s, &game->spritex.width, &game->spritex.height);
	if (!game->spritex.img)
		return (free_window(game));
	game->spritex.addr = (int *)mlx_get_data_addr(game->spritex.img,
			&game->spritex.bits_per_pixel,
			&game->spritex.line_length, &game->spritex.endian);
	if (!game->spritex.addr)
		return (free_window(game));
	return (1);
}

int	texture_to_img(t_game *game)
{
	int		j;
	char	*dir[5];

	j = -1;
	dir[0] = game->config.no;
	dir[1] = game->config.so;
	dir[2] = game->config.we;
	dir[3] = game->config.ea;
	dir[4] = 0;
	while (++j < 4)
	{
		game->tex[j].img = mlx_xpm_file_to_image(game->mlx,
				dir[j], &game->tex[j].width, &game->tex[j].height);
		if (!game->tex[j].img)
			return (free_window(game));
		game->tex[j].addr = (int *)mlx_get_data_addr(game->tex[j].img,
				&game->tex[j].bits_per_pixel,
				&game->tex[j].line_length, &game->tex[j].endian);
		if (!game->tex[j].addr)
			return (free_window(game));
	}
	if (BNS)
		return (sprite_texture(game));
	return (1);
}
