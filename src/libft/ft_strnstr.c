/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:35:05 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/13 23:42:06 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!haystack && !len)
		return (0);
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && needle[j] && i < len)
	{
		j = 0;
		if (haystack[i] != needle[j])
				i++;
		while (haystack[i] == needle[j] && needle[j] && i < len)
		{
			j++;
			i++;
		}
		if (needle[j] == '\0')
			return (((char *)haystack) + i - j);
	}
	return (NULL);
}
