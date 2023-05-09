/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_in_parent.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:30:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:52:22 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exicut_bultins(int c_of_s, int output_buckup, int input_buckup)
{
	c_of_s = builtins_in_parent(c_of_s);
	if (c_of_s != 0)
		return (c_of_s);
	dup2(output_buckup, STDOUT_FILENO);
	dup2(input_buckup, STDIN_FILENO);
	close(output_buckup);
	close(input_buckup);
	return (0);
}

void	return_fils_to_default(int output_buckup, int input_buckup)
{
	dup2(output_buckup, STDOUT_FILENO);
	dup2(input_buckup, STDIN_FILENO);
	close(output_buckup);
	close(input_buckup);
}

int	_parent_builtins(int c_of_s)
{
	if (g_struct.number_of_pipes == 1 && if_builtins_in_parent(c_of_s))
	{
		if (g_struct.each_cmd[c_of_s].files)
			return (rederaction_and_builtins(c_of_s));
		else
			c_of_s = builtins_in_parent(c_of_s);
		if (c_of_s == 1)
		{
			free_all_v2(0);
			return (0);
		}
		if (c_of_s == -1)
		{
			free_all_v2(0);
			return (1);
		}
	}
	return (2);
}

int	rederaction_and_builtins(int c_of_s)
{
	int	output_buckup;
	int	input_buckup;

	output_buckup = dup(STDOUT_FILENO);
	input_buckup = dup(STDIN_FILENO);
	c_of_s = check_rediractions_in_parent(c_of_s);
	if (c_of_s == -1)
	{
		return_fils_to_default(output_buckup, input_buckup);
		return (0);
	}
	if (c_of_s == 1)
	{
		return_fils_to_default(output_buckup, input_buckup);
		return (1);
	}
	c_of_s = exicut_bultins(c_of_s, output_buckup, input_buckup);
	if (c_of_s != 0)
		return (c_of_s);
	return (0);
}
