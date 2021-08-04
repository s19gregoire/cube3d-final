/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:13:54 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:17:12 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	initialise_map(t_map *map)
{
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	map->s = 0;
	map->maze = (char **)malloc(sizeof(char *) * FILESIZE);
	*map->maze = NULL;
	map->line = 0;
	map->trim = 0;
	map->idx = 0;
	map->x = -1;
	map->y = -1;
	map->start_wall = -1;
	map->end_wall = -1;
	map->sprites = 0;
	map->f_check = 0;
	map->c_check = 0;
	map->complete = 0;
	map->end = 0;
}

static void	extension_checker(char *path, t_map *map)
{
	int	l;

	l = ft_strlen(path);
	if (ft_strcmp(&path[l - 4], ".cub"))
	{
		get_error('e');
		free_map(map);
		exit(0);
	}
}

static int	loadercube3d(char **av)
{
	t_map	*map;
	int		game;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	initialise_map(map);
	extension_checker(av[1], map);
	game = read_map(map, av);
	if (game < 0)
	{
		free_map(map);
		return (0);
	}
	start_game(*map);
	free_map(map);
	return (1);
}

int	main(int ac, char **av)

{
	if (ac != 2)
		printf("Error\nInvalid number of arguments.\n");
	else
		loadercube3d(av);
	return (0);
}
