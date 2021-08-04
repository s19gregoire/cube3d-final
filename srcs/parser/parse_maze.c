/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maze.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:10:10 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:10:15 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_startwall(t_map *map, char *l, int y)
{
	if (l[y] && l[y] != '1')
		return (get_error('w'));
	map->start_wall = y;
	return (0);
}

int	get_endwall(t_map *map, char *l)
{
	int	e;

	e = ft_strlen(l) - 1;
	while (l[e] && ft_isspace(l[e]))
		e--;
	if (l[e] != '1')
		return (get_error('w'));
	while (e > map->end_wall && !ft_ismaze(l[e]))
		e--;
	if (ft_ismaze(l[e]) && l[e + 1] != '1' && not_walled(e, map))
		return (get_error('w'));
	map->end_wall = e;
	return (0);
}

int	get_playerpos(t_map *map, int y)
{
	if (map->x != -1)
		return (-1);
	map->x = map->idx;
	map->y = y;
	return (y + 1);
}

int	get_maze(t_map *map)
{
	int	err;

	err = 0;
	if (map->idx == 0)
		err = check_top_wall(map);
	else
		err = check_walls(map, map->line);
	if (!err && map->idx == 1)
		err = check_if_walled(map, map->line);
	map->maze[map->idx] = ft_strdup(map->line);
	map->idx++;
	map->maze[map->idx] = 0;
	if (!map->maze[map->idx - 1])
		return (1);
	return (err);
}
