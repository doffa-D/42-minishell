/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:09:21 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 16:16:33 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ftstrchr(char c, char const *set)
{
	int	j;

	j = 0;
	while (set[j])
	{
		if (set[j] == c)
			return (1);
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s1ln;
	char	*b;

	i = 0;
	if (s1 == 0)
		return (0);
	if (set == 0)
		return ((char *)s1);
	s1ln = ft_strlen(s1) - 1;
	while (ftstrchr(s1[i], set))
		i++;
	while (ftstrchr(s1[s1ln], set) && s1ln > 0)
		s1ln--;
	if (i > s1ln)
		return (ft_substr(s1, i, 0));
		b = ft_substr(s1, i, s1ln - i +1);
	return (b);
}
