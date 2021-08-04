/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:21:28 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:21:30 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	empty_line(char **line)
{
	*line = ft_strdup("");
	if (!*line)
		return (-1);
	return (0);
}

static int	file_error(char **keep, int fd)
{
	if (keep[fd])
		free(keep[fd]);
	return (0);
}

static int	ft_eof(int input, char **keep, char **line, int fd)
{
	if (input < 0)
		return (-1);
	else if (!input && !keep[fd])
		return (empty_line(line));
	return (0);
}

char	*ft_update_static(char **keep, char *buf, int fd)
{
	char	*tmp;

	if (!keep[fd])
	{
		keep[fd] = ft_strdup("");
		if (!keep[fd])
		{
			if (buf)
				free(buf);
			return (NULL);
		}
	}
	tmp = ft_join(keep[fd], buf);
	if (!tmp)
	{
		ft_free(&keep[fd]);
		free(buf);
		return (NULL);
	}
	ft_free(&keep[fd]);
	keep[fd] = ft_strdup(tmp);
	free(tmp);
	return (keep[fd]);
}

int	get_next_line(int fd, char **line, int err)
{
	int			input;
	char		*buf;
	static char	*keep[FOPEN_MAX];

	if (err)
		return (file_error(keep, fd));
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX || !line || !buf)
		return (ft_return(keep, -1));
	input = read(fd, buf, BUFFER_SIZE);
	while (input > 0)
	{
		buf[input] = '\0';
		keep[fd] = ft_update_static(keep, buf, fd);
		if (!keep[fd])
			return (-1);
		if (ft_strchr(keep[fd], '\n') > -1)
			break ;
		input = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (input < 0 || (!input && !keep[fd]))
		return (ft_eof(input, keep, line, fd));
	return (ft_fill_line(keep, line, fd));
}
