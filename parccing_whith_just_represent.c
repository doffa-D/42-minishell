/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccing_whith_just_represent.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:49:58 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 13:50:12 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
			ft_putstr_fd
				("minishell: unexpected EOF while looking for matching\n", 2);
			return (2);
		}
		g_struct.the_commande = ft_strjoin_v2(g_struct.the_commande, \
			g_struct.fix_cmd[variables->index_i]);
		if (g_struct.fix_cmd[variables->index_i + 1])
			g_struct.the_commande = ft_strjoin(g_struct.the_commande, \
			"\003\000");
		g_struct.fix_cmd[variables->index_i] = 0;
		variables->index_i++;
	}
	return (1);
}