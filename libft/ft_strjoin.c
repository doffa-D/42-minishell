/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:55:01 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 15:58:36 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*b;
	int		j;

	if (!s1 || !s2)
		return (0);
	b = malloc((ft_strlen(s1) + 1) + ft_strlen(s2));
	if (!b)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		b[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		b[i] = s2[j];
		i++;
		j++;
	}
	b[i] = '\0';
	return (b);
}
