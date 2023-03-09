/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:29:04 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 15:35:32 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dst;
	int		i;
	int		len;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	dst = malloc(len + 1);
	if (!dst)
		return (0);
	while (s[i] != 0)
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = 0;
	return (dst);
}
