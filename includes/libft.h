/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 10:46:12 by mlazzare          #+#    #+#             */
/*   Updated: 2021/06/09 07:35:34 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFFER_SIZE 100

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define MAX_LONG	9223372036854775807

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isspace(char c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);
int				ft_numlen(long n);
int				ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);

/* get_next_line */

int				get_next_line(int fd, char **line, int err);
int				ft_fill_line(char **keep, char **line, int fd);
int				ft_return(char **keep, int ret);
char			*ft_join(char *s1, char *s2);
char			*ft_update_static(char **keep, char *buf, int fd);
void			ft_free(char **line);

#endif
