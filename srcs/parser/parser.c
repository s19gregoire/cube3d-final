/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:10:45 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:10:48 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	wrong_line_setup(t_map *map)
{
	if (!map->line)
		return (get_error('l'));
	map->trim = trimspaces(map->line);
	if (!map->trim)
		return (get_error('l'));
	return (0);
}

int	fill_map(t_map *map, int err)
{
	if (wrong_line_setup(map))
		return (1);
	if (ft_strcmp(map->trim, ""))
	{
		if (map->trim[0] == 'N' && !map->no)
			err = get_path(map, map->trim);
		else if (map->trim[0] == 'S' && map->trim[1] == 'O' && !map->so)
			err = get_path(map, map->trim);
		else if (map->trim[0] == 'W' && !map->we)
			err = get_path(map, map->trim);
		else if (map->trim[0] == 'E' && !map->ea)
			err = get_path(map, map->trim);
		else if (BNS && ft_issprite(map->trim[0], map->trim[1]) && !map->s)
			err = get_sprite_path(map, map->trim);
		else if (map->trim[0] == 'C' && !map->c_check)
			err = get_rgb_value(map, map->c, map->trim);
		else if (map->trim[0] == 'F' && !map->f_check)
			err = get_rgb_value(map, map->f, map->trim);
		else if (map_checked(map))
			err = get_maze(map);
		else
			err = get_error('x');
	}
	free_line(map->trim);
	return (err);
}

static int	check_lastline(t_map *map, int space)
{
	if (!space && check_bottom_wall(map, map->maze[map->idx - 1]))
		return (get_error('w'));
	map->maze[map->idx] = ft_strdup("");
	if (!map->maze[map->idx])
		return (1);
	map->idx++;
	map->maze[map->idx] = 0;
	return (0);
}

static int	read_line(int fd, int gnl, int err, t_map *map)
{
	int	space;

	space = 0;
	while (fd && gnl)
	{
		gnl = get_next_line(fd, &map->line, err);
		if (err)
			break ;
		if (space && !ft_strcmp(map->line, ""))
			err = check_lastline(map, space);
		else if (map->line && ft_strcmp(map->line, ""))
		{
			err = check_line(err, space, map);
			space = check_emptyline(map->line, map);
			if (space < 0)
				err = 1;
		}
		else if (gnl && map->line && map->idx > 0 && !ft_strcmp(map->line, ""))
		{
			err = check_lastline(map, space);
			space = 1;
		}
		free_line(map->line);
	}
	return (check_err(err, space, map));
}

int	read_map(t_map *map, char **av)
{
	int		fd;
	int		err;
	int		gnl;

	err = 0;
	gnl = 1;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (-get_error('o'));
	err = read_line(fd, gnl, err, map);
	if (close(fd) < 0)
		return (get_error('o'));
	return (check_map(map, err));
}
