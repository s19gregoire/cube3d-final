/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:08:23 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:08:28 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_cf(char *line)
{
	return ((line[0] == 'F' || line[0] == 'C')
		&& ft_isspace(line[1]));
}

int	skip_space(char *l, int i)
{
	while (l[i] && ft_isspace(l[i]))
		i++;
	return (i);
}

int	check_spaces(int pos, t_map *map, char *l)
{
	if (l[pos - 1] != '1')
		return (-1);
	while (l[pos] && ft_isspace(l[pos]) && not_walled(pos, map))
		pos++;
	if (l[pos] && l[pos] != '1')
		return (-1);
	if (l[pos])
		return (pos + 1);
	return (pos);
}

int	check_emptyline(char *line, t_map *map)
{
	char	*r;

	if (map->idx == 0)
		return (0);
	r = trimspaces(line);
	if (!r)
		return (-1);
	if (ft_strcmp(r, ""))
	{
		free(r);
		return (0);
	}
	free(r);
	return (1);
}

int	check_line(int err, int space, t_map *map)
{
	err = fill_map(map, err);
	if (!err && space && map->idx > 0)
		err = check_top_wall(map);
	return (err);
}
