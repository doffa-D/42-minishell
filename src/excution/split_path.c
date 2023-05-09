/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:32:14 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	_path_comanmde(void)
{
	int		i;
	int		j;
	char	*path;
	char	*str;

	i = -1;
	j = 0;
	path = ft_strdup("");
	str = my_getenv(g_struct.list, "PATH", 0);
	while (str[++i])
	{
		if (str[i] == ':' && (str[i + 1] != ':'))
		{
			path = ft_strjoin_v2(path, ft_substr(str, j, i - j));
			j = i;
			if (i == 0 || i == (int)ft_strlen(str) \
			|| (str[i - 1] && str[i - 1] == ':'))
			{
				path = ft_strjoin(path, ".");
				i++;
			}
		}
	}
	free(str);
	g_struct.my_path = ft_split(path, ':');
	free(path);
}