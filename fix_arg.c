/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/23 13:11:31 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	char	*b;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
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


int count_2d(t_all *my_struct)
{
    my_struct->command_len = -1;
    while(my_struct->fix_cmd[++my_struct->command_len]);
    return my_struct->command_len;
}


int     ft_strcher_v2(char *str,char c,int i)
{
    
    while(str[i])
    {
        if(str[i] == c)
        {
            return i;
        }
        i++;
    }

    return -1;
}
char  *checker(char *cmd, t_all *my_struct)
{
    int i = 0;
    int j = 0;
    my_struct->error = 0;

    char *str = ft_calloc(ft_strlen(cmd) + 1, 1);
    while(cmd[i] && my_struct->error == 0)
    {
        
        if(cmd[i] == 34)
        {
            j = ft_strcher_v2(cmd, 34, i + 1);
            if(j == -1)
                    my_struct->error = 1;

            str = ft_strjoin_v2(str, ft_substr(cmd, i + 1, j - i - 1));
            i = j;
        }
        else if(cmd[i] == 39)
        {
            j = ft_strcher_v2(cmd, 39, i + 1);
            if(j == -1)
                my_struct->error = 1;
            str = ft_strjoin_v2(str, ft_substr(cmd, i + 1, j - i - 1));
            i = j;
        }
        else
        {
            str = ft_strjoin_v2(str, ft_substr(cmd, i,1));
        }
        i++;
    }
    return str;
}

char *check_inve(char **split,int i)
{
    int x;
    x = 0;
    char *backup = ft_strdup("");
    while(--i >= 0)
    {
        if(ft_strchr(split[i],'$'))
        {
            if(getenv(&split[i][1]) != NULL)
            {
                backup = ft_strjoin(backup,getenv(&split[i][1]));
            }
        }
        else
		    backup = ft_strjoin(backup,split[i]);

    }
    return backup;
}


int counter_malloc(char *cmd)
{
    char *dst = ft_strdup(cmd);
    int i;
    int x;
    x = 0;
    i = ft_strlen(dst)-1;
    while(i >= 0)
    {
        if(dst[i] == '$' || i == 0 || dst[i] == 34 || dst[i] == 39)
        {
            dst[i] = '\0';
            x++;
        }
        i--;
    }
    return (x);
}

char *split_dollar(char *cmd)
{
    char **split;
    char *dst;
    int i;
    int x;
    x = 0;
    i = ft_strlen(cmd)-1;
    split = calloc(sizeof(char *)* counter_malloc(cmd) + 1 , 1);
    while(i >= 0)
    {
        if(cmd[i] == '$' || i == 0 || cmd[i] == 34 || cmd[i] == 39)
        {
            split[x] = ft_strdup(&cmd[i]);
            cmd[i] = '\0';
            x++;
        }
        i--;
    }
    dst = check_inve(split,x);
    return (dst);
}
char    *dollar_handle(char *cmd)
{
    cmd = split_dollar(cmd);
    return cmd;
}

void    fill(t_all *my_struct)
{
    int i;
    i = 0;

    while(my_struct->fix_cmd[i])
    {
        my_struct->fix_cmd[i] = checker(my_struct->fix_cmd[i], my_struct);
        i++;
    }             
}

int mini_checker(char *cmd)
{
    if(cmd[0] == 34 && cmd[ft_strlen(cmd)-1] == 34)
        return 0;
    else if(cmd[0] == 39 && cmd[ft_strlen(cmd)-1] == 39)
        return 1;
    return -1;
}

void    fix_arg(t_all *my_struct)
{
    int i;
    int j;
    j = 0;
    i = 0;
    char *cmd;
    my_struct->my_command = malloc(sizeof(char *) * (count_2d(my_struct)+1));
    fill(my_struct);
    while(my_struct->fix_cmd[i] && my_struct->error == 0)
    {
        // printf("[[%d]]\n",my_struct->error);
        if(mini_checker(my_struct->fix_cmd[i]) == 0 || mini_checker(my_struct->fix_cmd[i]) == -1)
        {
            if(ft_strchr(my_struct->fix_cmd[i],'$'))
            {

                cmd = dollar_handle(my_struct->fix_cmd[i]);
                if(cmd != 0)
                    my_struct->my_command[j] = cmd;
                else
                    my_struct->my_command[j] = 0;
            }
            else
                my_struct->my_command[j] = my_struct->fix_cmd[i];
            j++;
        }
        else if(mini_checker(my_struct->fix_cmd[i]) == 1)
        {
            my_struct->my_command[j] = my_struct->fix_cmd[i];
            j++;
        }
        i++;
    }
    if(my_struct->error == 1)
        printf("error\n");
    my_struct->my_command[j] = 0;
    // j = 0;
    // while(my_struct->my_command[j])
    // {
    //     printf("{{{%s}}}\n",my_struct->my_command[j]);
    //     j++;
    // }
}