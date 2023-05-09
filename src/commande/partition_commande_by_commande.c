/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_commande_by_commande.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:52:38 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 17:52:41 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_parccing_part_after_error(void *malloc_error)
{
	int	i;

	i = 0;
	if (!malloc_error)
	{
		while (g_struct.splite_pipe[i])
		{
			free(g_struct.splite_pipe[i]);
			i++;
		}
		free_commande_whit_out_path(0, 0);
		free_linked_list();
		exit(1);
	}
}

int	partition_of_comande_and_rederaction(t_var *variables, int c_of_s)
{
	g_struct.status = OUTSIDE;
	g_struct.tmp_cmd = ft_strdup(g_struct.splite_pipe[variables->index_i]);
	free_parccing_part_after_error(g_struct.tmp_cmd);
	variables->index_j = 0;
	g_struct.the_commande = ft_calloc(1, 1);
	free_parccing_part_after_error(g_struct.tmp_cmd);
	if_rediraction_is_existe(variables);
	c_of_s = 0;
	variables->index_j = 0;
	while (g_struct.tmp_cmd[variables->index_j])
	{
		g_struct.parccer = 0;
		c_of_s = commande_and_rederaction_parceen(variables, \
			c_of_s);
		if (c_of_s < 0)
			return (c_of_s);
		variables->index_j++;
	}
	quotes_comnde(variables);
	free(g_struct.splite_pipe[variables->index_i]);
	g_struct.splite_pipe[variables->index_i] = 0;
	free(g_struct.the_commande);
	g_struct.the_commande = 0;
	return (0);
}

int	partition_part(t_var *variables)
{
	int	c_of_s;

	c_of_s = 0;
	variables->end = 0;
	variables->index_i = 0;
	g_struct.fils_descreprot = 0;
	while (g_struct.splite_pipe[variables->index_i])
	{
		c_of_s = partition_of_comande_and_rederaction(variables, c_of_s);
		if (c_of_s != 0)
			return (c_of_s);
		variables->index_i++;
	}
	free(g_struct.splite_pipe);
	return (0);
}
