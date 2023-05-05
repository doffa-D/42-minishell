/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:11 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/05 20:29:34 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int get_the_path(t_all *_struct ,int c_of_s)
{
    int i = 0;
    while (_struct->my_path && _struct->my_path[i])
    {
        if(_struct->each_cmd[c_of_s].cmd && _struct->each_cmd[c_of_s].cmd[0] \
        && *_struct->each_cmd[c_of_s].cmd[0])
        {
            _struct->my_path[i] = ft_strjoin(_struct->my_path[i], "/");
	        _struct->my_path[i] = ft_strjoin(_struct->my_path[i], _struct->each_cmd[c_of_s].cmd[0]);
            i++;
        }
		else
            return 1;
    }
    return 0;
}
