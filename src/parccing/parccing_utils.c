/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:18:12 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	char	*b;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = -1;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[++i])
		b[i] = s1[i];
	while (s2[j])
	{
		b[i] = s2[j];
		i++;
		j++;
	}
	b[i] = 0;
	free((char *)s1);
	free((char *)s2);
	return (b);
}

char	*expande_variables_insied_herdoc(t_var *indes, char *buffer,
		char *herdoc)
{
	char	*buffer_tmp;

	indes->start = indes->index_i;
	while (ft_isalnum(buffer[indes->index_i]) \
	|| buffer[indes->index_i] == '_')
		indes->index_i++;
	buffer_tmp = ft_substr(buffer, indes->start, indes->index_i - indes->start);
	free_parccing_part_after_error(buffer_tmp);
	herdoc = ft_strjoin_v2(herdoc, my_getenv(g_struct.list, buffer_tmp, 0));
	free_parccing_part_after_error(herdoc);
	free(buffer_tmp);
	indes->start = indes->index_i;
	return (herdoc);
}

int	other_string_beffor_end_of_line(t_var *variables, int cas)
{
	variables->start++;
	g_struct.tmp_cmd = ft_strjoin_v2(g_struct.tmp_cmd, \
	ft_substr(g_struct.each_cmd[variables->index_i].cmd \
	[variables->end], variables->start, variables->index_j \
	- variables->start));
	free_parccing_part_after_error(g_struct.tmp_cmd);
	free(g_struct.each_cmd[variables->index_i].cmd[variables->end]);
	g_struct.each_cmd[variables->index_i].cmd[variables->end] = 0;
	if (!(ft_strchr(g_struct.tmp_cmd, 7) && \
		ft_strlen(g_struct.tmp_cmd) == 1))
	{
		g_struct.each_cmd[variables->index_i].cmd[cas] \
		= ft_strdup(g_struct.tmp_cmd);
		free_parccing_part_after_error(g_struct.each_cmd \
		[variables->index_i].cmd[cas]);
		cas++;
	}
	free(g_struct.tmp_cmd);
	g_struct.tmp_cmd = 0;
	variables->end++;
	return (cas);
}
