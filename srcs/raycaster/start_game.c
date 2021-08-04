/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:12:13 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:12:14 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	swap_frame(t_game *game)
{
	void	*frame;
	void	*adr;

	if (game->img.counter % 2 == 0)
	{
		frame = game->img.img;
		game->img.img = game->img.img2;
		game->img.img2 = frame;
		adr = game->img.addr;
		game->img.addr = game->img.addr2;
		game->img.addr2 = adr;
	}
	else
	{
		frame = game->img.img2;
		game->img.img2 = game->img.img;
		game->img.img = frame;
		adr = game->img.addr2;
		game->img.addr2 = game->img.addr;
		game->img.addr = adr;
	}
	game->img.counter++;
}

static int	game_loop(t_game *game)
{	
	if (game->win)
	{
		draw_3d(game);
		if (BNS)
			draw_2dmap(game);
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
		move_backforwards(game);
		move_leftright(game);
		rotate_view(game, game->player.initx, game->player.planex);
		swap_frame(game);
		return (0);
	}
	return (-1);
}

static int	set_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->winW,
			game->winH, "raycasting");
	if (!game->win)
		return (free_window(game));
	game->img.img = mlx_new_image(game->mlx, game->winW,
			game->winH);
	game->img.addr = (int *)mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->img.img2 = mlx_new_image(game->mlx, game->winW,
			game->winH);
	game->img.addr2 = (int *)mlx_get_data_addr(game->img.img2,
			&game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->img.counter = 0;
	if (!game->img.img || !game->img.img2
		|| !game->img.addr || !game->img.addr2)
		return (free_dataimg(game));
	return (1);
}

int	start_game(t_map map)
{
	int		g;
	t_game	game;

	g = init_game(&game, map);
	if (!g)
		return (get_error('y') - 1);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (get_error('y') - 1);
	if (!texture_to_img(&game) || !set_window(&game))
		return (0);
	mlx_hook(game.win, 33, 1L << 17, x_exit, &game);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
	free(game.mlx);
	return (1);
}
