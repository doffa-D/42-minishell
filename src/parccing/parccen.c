/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parccen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/14 03:54:27 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	fix_arg_utils(t_var *variables)
{
	g_struct.splite_pipe = ft_split(g_struct.the_commande, 4);
	if (!g_struct.splite_pipe)
	{
		free_linked_list();
		free(g_struct.each_cmd);
		free(g_struct.the_commande);
		exit(1);
	}
	free(g_struct.the_commande);
	g_struct.the_commande = 0;
	variables->index_i = 0;
	g_struct.fils_descreprot = 0;
	variables->index_i = partition_part(variables);
	if (variables->index_i == -1)
		return (258);
	if (variables->index_i == -2)
		return (1);
	return (0);
}

void	init(t_var	*variables)
{
	variables->index_i = 0;
	variables->index_j = 0;
	variables->start = -1;
	g_struct.number_of_pipes = 1;
	g_struct.the_commande = 0;
	g_struct.the_commande = ft_calloc(1, 1);
	if (!g_struct.the_commande)
	{
		free_linked_list();
		exit(1);
	}
}

int	fix_arg(void)
{
	t_var	variables;

	init(&variables);
	variables.index_i = parcing_part(&variables);
	if (variables.index_i != 1)
		return (variables.index_i);
	free(g_struct.fix_cmd);
	g_struct.each_cmd = ft_calloc(sizeof(t_each_command),
			g_struct.number_of_pipes + 1);
	if (!g_struct.each_cmd)
	{
		free_linked_list();
		free(g_struct.the_commande);
		exit(1);
	}
	variables.index_i = fix_arg_utils(&variables);
	if (variables.index_i != 0)
		return (variables.index_i);
	return (0);
}
