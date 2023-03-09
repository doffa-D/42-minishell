/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:49:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 15:22:03 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	char		*s;

	d = (char *)dest;
	s = (char *)src;
	i = 0;
	if (d == 0 && s == 0)
		return (0);
	while (i < n)
	{
		*(d + i) = *(s + i);
		i++;
	}
	return (d);
}
