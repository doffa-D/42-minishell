/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:32:14 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 19:33:42 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_in_error(void)
{
	free_all_v2(0);
	free_linked_list();
	exit(1);
}

char	*beffor_split_path(int i, char *str, int j, char *path)
{
	if (str[i] == ':' && (str[i + 1] != ':'))
	{
		path = ft_strjoin_v2(path, ft_substr(str, j, i - j));
		if (!path)
			free_in_error();
		j = i;
		if (i == 0 || i == (int)ft_strlen(str) \
		|| (str[i - 1] && str[i - 1] == ':'))
		{
			path = ft_strjoin(path, ".");
			if (!str)
				free_in_error();
			i++;
		}
	}
	return (path);
}

void	_path_comanmde(int i)
{
	int		j;
	char	*path;
	char	*str;

	i = -1;
	j = 0;
	path = ft_strdup("");
	if (!path)
		free_in_error();
	str = my_getenv(g_struct.list, "PATH", 0);
	if (!str)
		free_in_error();
	while (str[++i])
	{
		path = beffor_split_path(i, str, j, path);
	}
	free(str);
	g_struct.my_path = ft_split(path, ':');
	if (!g_struct.my_path)
		free_in_error();
	free(path);
}