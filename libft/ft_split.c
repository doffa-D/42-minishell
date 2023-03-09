/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:38:31 by hdagdagu          #+#    #+#             */
/*   Updated: 2022/10/11 16:29:34 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_alloc(char *s, char **dst, char c)
{
	int		j;
	char	*tmp_s;

	tmp_s = s;
	j = 0;
	while (*tmp_s != 0)
	{
		while (*s == c)
			s++;
		tmp_s = s;
		while (*tmp_s && *tmp_s != c)
			++tmp_s;
		if (*tmp_s == c || s < tmp_s)
		{
			dst[j] = ft_substr(s, 0, ft_strlen(s) - ft_strlen(tmp_s));
			if (dst[j] == 0)
				return (0);
			s = tmp_s;
			j++;
		}
	}
	return (dst);
}

int	ft_count(const char *s, char c)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			if (s[i + 1] == c || !s[i + 1])
				j++;
			i++;
		}
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	int		j;

	j = 0;
	if (s == 0)
		return (0);
	j = ft_count(s, c);
	dst = (char **)ft_calloc(sizeof(char *), (j + 1));
	if (dst == 0)
		return (0);
	ft_alloc((char *)s, dst, c);
	return (dst);
}
