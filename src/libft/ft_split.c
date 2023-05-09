/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:55:59 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 22:00:23 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	**complate(const char *sp, char c, size_t j)
{
	char		**splt;
	const char	*b;
	int			i;

	b = sp;
	splt = ft_calloc((j + 1), sizeof(char *));
	j = 0;
	while (*sp)
	{
		i = 0;
		while (sp[i] == c)
		{
			sp++;
			b++;
		}
		while (*sp != c && *sp)
		{
			i++;
			sp++;
		}
		splt[j] = ft_substr(b, 0, i);
		b = sp;
		j++;
	}
	return (splt);
}

char	**ft_split(char const *s, char c)
{
	size_t		j;
	int			i;
	char		**splt;
	char		set[2];

	if (!s)
		return (0);
	i = 0;
	j = 1;
	set[0] = c;
	set[1] = 0;
	s = ft_strtrim(s, set);
	if (!s)
		return (0);
	while (s[i] != 0)
	{
		if (s[i] == c)
			j++;
		while (s[i] == c)
			i++;
		i++;
	}
	splt = complate(s, c, j);
	free((char *)s);
	return (splt);
}
