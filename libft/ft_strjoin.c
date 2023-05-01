/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:38:28 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/01 21:04:50 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*b;
	int		i;
	int		j;
	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		b[i] = s2[j];
		i++;
		j++;
	}
	b[i] = 0;
	free((char *)s1);
	return (b);
}
