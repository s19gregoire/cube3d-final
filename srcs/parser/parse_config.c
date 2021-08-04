/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:08:38 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:08:42 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_cf(t_map *map, char c)
{
	if (c == 'F')
		map->f_check = 1;
	else if (c == 'C')
		map->c_check = 1;
}

static int	get_direction(t_map *map, char *li, int i)
{
	char	*r;

	r = trimspaces(&li[i]);
	if (!r)
		return (0);
	if (li[0] == 'N')
		map->no = ft_strdup(&li[i]);
	else if (li[0] == 'S')
		map->so = ft_strdup(&li[i]);
	else if (li[0] == 'W')
		map->we = ft_strdup(&li[i]);
	else if (li[0] == 'E')
		map->ea = ft_strdup(&li[i]);
	free(r);
	return (1);
}

int	get_path(t_map *map, char *line)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!(ft_isdirection(line, i) && ft_isspace(line[2])))
		return (get_error('d'));
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	if (!(line[i] == '.' && line[i + 1] == '/'))
		return (get_error('t'));
	start = i;
	i += 2;
	while (line[i] && (ft_isalpha(line[i]) || line[i] == '/'))
		i++;
	if (!get_direction(map, line, start))
		return (1);
	map->complete++;
	return (0);
}

int	get_sprite_path(t_map *map, char *line)
{
	int		i;
	int		start;
	char	*r;

	i = 0;
	start = 0;
	if (!(line[i] == 'S' && ft_isspace(line[i + 1])))
		return (get_error('d'));
	i += 2;
	while (ft_isspace(line[i]))
		i++;
	if (!(line[i] == '.' && line[i + 1] == '/'))
		return (get_error('r'));
	start = i;
	i += 2;
	while (line[i] && (ft_isalpha(line[i]) || line[i] == '/'))
		i++;
	r = trimspaces(&line[start]);
	if (!r)
		return (1);
	map->s = ft_strdup(r);
	map->complete++;
	free(r);
	return (0);
}

int	get_rgb_value(t_map *map, int *s, char *line)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!check_cf(line))
		return (get_error('g'));
	update_cf(map, line[i]);
	while (line[i++])
	{
		i = skip_space(line, i);
		if (!(ft_isdigit(line[i]) && ++j < 3))
			return (get_error('g'));
		s[j] = ft_atoi(&line[i]);
		if (s[j] < 0 || s[j] > 255)
			return (get_error('g'));
		i += ft_numlen(s[j]);
		i = skip_space(line, i);
		if (line[i] && line[i] != ',' && j != 2)
			return (get_error('g'));
	}
	if (j != 2)
		return (get_error('g'));
	map->complete++;
	return (0);
}
