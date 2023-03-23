/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tet.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 12:06:48 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/21 13:06:08 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int     checker(char *str,char c)
{
    int i;
    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return i;
        i++;
    }
    return 0;
}


int main(int argc,char **argv)
{

    int i;
    int j;
    j = 0;
    i = 0;
    char *cmd = argv[1];
    char *dst;
    while(cmd[i])
    {
        if(cmd[i] == 34)
        {
            j = checker(&cmd[i+1],34);
            if(j != 0)
            {
                dst = ft_substr(cmd,i,j - i);
                printf("%s",dst);
            }
        }
        i++;
    }
}