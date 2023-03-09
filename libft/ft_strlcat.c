/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:44:26 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 15:25:45 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{	
	size_t	destlen;
	size_t	d;
	size_t	result;

	if (n == 0 && (!dst || !src))
		return (ft_strlen(src));
	result = (ft_strlen(dst) + ft_strlen(src));
	destlen = ft_strlen(dst);
	if (n <= destlen)
		return (n + ft_strlen(src));
	d = 0;
	while (src[d] != 0 && n > destlen + 1)
	{
		dst[destlen] = src[d];
		destlen++;
		d++;
	}
	dst[destlen] = '\0';
	return (result);
}
