/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:17:56 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/20 19:09:03 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat( char *dst, const char *src, size_t size)
{
	size_t		b;
	size_t		c;
	size_t		a;
	size_t		i;

	if (size == 0 && (!dst || !src))
		return (ft_strlen(src));
	c = ft_strlen(src);
	b = ft_strlen((const char *)dst);
	a = 0;
	if (size <= b)
		return (c + size);
	else
		i = b + c;
	while (src[a] && b < size -1)
	{
		dst[b] = src[a];
		a++;
		b++;
	}
	dst[b] = 0;
	return (i);
}
