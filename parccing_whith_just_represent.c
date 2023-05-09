/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_whith_just_represent.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:49:58 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 01:47:34 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_all(t_var *variables)
{
	g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
		g_struct.fix_cmd[variables->index_i]);
	if (!g_struct.the_commande)
	{
		while (g_struct.fix_cmd[variables->index_i])
		{
			free(g_struct.fix_cmd[variables->index_i]);
			variables->index_i++;
		}
		exit(1);
	}
	if (g_struct.fix_cmd[variables->index_i + 1])
	{
		g_struct.the_commande = ft_strjoin(g_struct.the_commande, "\003\000");
		if (!g_struct.the_commande)
		{
			while (g_struct.fix_cmd[variables->index_i])
			{
				free(g_struct.fix_cmd[variables->index_i]);
				variables->index_i++;
			}
			exit(1);
		}
	}
}

int	parccen_part(t_var *variables)
{
	while (g_struct.fix_cmd[variables->index_i])
	{
		variables->index_j = 0;
		g_struct.status = OUTSIDE;
		if (change_quotes_and_pipe_and_rederaction(variables) == 258)
			return (258);
		if (g_struct.status != OUTSIDE)
		{
			ft_putstr_fd \
			("minishell: unexpected EOF while looking for matching\n", 2);
			while (g_struct.fix_cmd[variables->index_i])
			{
				free(g_struct.fix_cmd[variables->index_i]);
				variables->index_i++;
			}
			free(g_struct.fix_cmd);
			free(g_struct.the_commande);
			return (2);
		}
		join_all(variables);
		g_struct.fix_cmd[variables->index_i] = 0;
		variables->index_i++;
	}
	return (1);
}
