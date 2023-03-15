/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:58:59 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/15 13:06:02 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*ds;
	char	*s;
	size_t	i;

	i = 0;
	if (dst == 0 && src == 0)
		return (dst);
	s = (char *)src;
	ds = (char *)dst;
	while (i < n)
	{
		ds[i] = s[i];
		i++;
	}
	return ((char *)dst);
}
