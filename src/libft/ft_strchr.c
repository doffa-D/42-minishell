/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 12:54:01 by nouakhro          #+#    #+#             */
/*   Updated: 2022/10/12 20:18:52 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	while (*str != 0)
	{
		if (*str != (char )chr)
			str++;
		else
			return ((char *)str);
	}
	if ((char)chr == '\0')
		return ((char *)str);
	return (0);
}
