/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:13:30 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:13:33 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->we)
		free(map->we);
	if (map->ea)
		free(map->ea);
	if (map->s)
		free(map->s);
	while (map->maze && map->maze[++i])
		free(map->maze[i]);
	if (map->maze)
		free(map->maze);
	free(map);
}

static void	free_bonus(t_game *game)
{
	if (game->spritex.img)
		mlx_destroy_image(game->mlx, game->spritex.img);
	if (game->zbuf)
		free(game->zbuf);
	if (game->sprites)
		free(game->sprites);
}

void	free_game(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
	if (BNS && game->spritex.img)
		mlx_destroy_image(game->mlx, game->spritex.img);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->img.img2)
		mlx_destroy_image(game->mlx, game->img.img2);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = 0;
	if (BNS)
	{
		if (game->zbuf)
			free(game->zbuf);
		if (game->sprites)
			free(game->sprites);
	}
}

int	free_window(t_game *game)
{
	int	i;

	i = -1;
	printf("Error\nTexture file failed to open\nRetry\n");
	while (++i < 4)
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
	if (BNS)
		free_bonus(game);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}

int	free_dataimg(t_game *game)
{
	int	i;

	i = -1;
	printf("Error\nImage data failed to initialise\nRetry\n");
	while (++i < 4)
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
	if (BNS)
		free_bonus(game);
	if (game->img.img)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->img.img2)
		mlx_destroy_image(game->mlx, game->img.img2);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	game->win = 0;
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	return (0);
}
