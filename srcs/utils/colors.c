/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:12:47 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:12:49 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_pixel(t_game *game, int y, int x, int color)
{
	if (x < 0 || x > game->winW || y < 0 || y > game->winH)
		return ;
	game->img.addr[game->winW * y + x] = color;
}

int	get_colors(t_map *map, char c)
{
	if (c == 'c')
		return (map->c[2] << 16 | map->c[1] << 8 | map->c[0]);
	return (map->f[2] << 16 | map->f[1] << 8 | map->f[0]);
}
