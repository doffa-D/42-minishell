/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 11:48:56 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/04 09:52:38 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void const *src, size_t len)
{
	char	*ends;
	char	*endd;

	ends = (char *)src;
	endd = (char *)dest;
	if (ends == 0 && endd == 0)
		return (0);
	if (endd < ends)
		return (ft_memcpy(dest, src, len));
	else
	{
		while (len-- != 0)
			endd[len] = ends[len];
	}
	return (dest);
}
