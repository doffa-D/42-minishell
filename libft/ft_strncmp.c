/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:30:07 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 15:32:04 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *ss1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	s1 = (unsigned char *)ss1;
	i = 0;
	while (i < n && (s1[i] != 0 || s2[i] != 0))
	{
		if (s1[i] > s2[i] || (s1[i] && !s2[i]))
			return (1);
		else if (s1[i] < s2[i] || (!s1[i] && s2[i]))
			return (-1);
		i++;
	}
	return (0);
}
