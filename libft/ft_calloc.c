/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:23:10 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 15:19:26 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dest;
	size_t	s;

	if (count <= SIZE_MAX && size >= SIZE_MAX)
		return (0);
	s = (count * size);
	dest = (char *)malloc(s);
	if (!dest)
		return (0);
	ft_bzero(dest, s);
	return (dest);
}
