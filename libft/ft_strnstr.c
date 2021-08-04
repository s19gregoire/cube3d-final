/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneve <gneve@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:21:00 by gneve             #+#    #+#             */
/*   Updated: 2021/08/04 15:21:03 by gneve            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t				i;
	size_t				j;
	char				*ptr;

	ptr = (char *)big;
	if (!little[0])
		return (ptr);
	if (!len)
		return (NULL);
	i = 0;
	while (ptr[i] && i < len)
	{
		j = 0;
		while (ptr[i + j] == little[j] && i + j < len)
		{
			j++;
			if (little[j] == '\0')
				return (&ptr[i]);
		}
		i++;
	}
	return (NULL);
}
