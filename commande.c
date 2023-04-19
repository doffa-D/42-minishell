/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/19 23:38:04 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int mini_check_export(char *src)
{
	int i;

	i = 0;
	if(src[i] >= '0' && src[i] <= '9')
		return 1;
	while(src[i])
	{
		if(src[i] == '-')
			return 1;
		if((src[i] >= 33 && src[i] <= 38) || src[i] == 60 || (src[i] >= 40 && src[i] <= 47) || (src[i] >= 62 && src[i] <= 64) || (src[i] >= 91 && src[i] <= 94) || (src[i] >= 123 && src[i] <= 125))
			return 1;
		i++;
	}
	return 0;
}

int duplicate_check_export(t_list *list,char *dst)
{
	int i;
	i = 0;
	while(list != NULL)
	{

		if (!ft_strncmp(list->content, dst, ft_strlen(dst)+1))
			return i;
        list = list->next;
		i++;
	}
	return 0;
}

int mini_search(char *str,char c)
{
	int i;
	i = 0;
	while(str[i])
	{
		if(str[i]== c)
		{
			return i;

		}
		i++;
	}
	return 0;
}


void	add_node_back(char *str,t_list  **list)
{
	t_list  *new_node; 
	new_node = ft_lstnew(ft_strdup(str));
	ft_lstadd_back(list, new_node);
}

void	string_dakche(t_list *list)
{
	int x;
	int i;
	i = 0;
	char *backup;
	char *old;
	while(list != NULL)
	{
		i = 0;
		old = calloc(sizeof(char ),ft_strlen(list->content)+1);
		x = mini_search(list->content,'=');
		while(i <= x)
		{
			old[i] = ((char *)list->content)[i];
			i++;
		}
		backup = ft_strjoin_v2(old,ft_strdup(&((char *)list->content)[x+1]));
		free(list->content);
		list->content = ft_strdup(backup);
		free(backup);
		list = list->next;
	}
}
int	replace_varible(t_list *list,char *cmd)
{
	int i;
	int j;
	int x = 0;
	i = 0;
	j = 0;
	while(list != NULL)
	{
		i = 0;
		while(((char *)list->content)[i])
		{
			if(((char *)list->content)[i] == cmd[i] && cmd[i])
			{
				if(((char *)list->content)[i] == '=' || ((char *)list->content)[i+1] == '\0')
				{
					j = 1;
					break;
				}
				i++;
			}
			else
				break;
		}
		if(j == 1)
			break;
		list = list->next;
		x++;
	}
	char *old;
	char *backup = calloc(sizeof(char),ft_strlen(cmd)+1);
	if(j == 1)
	{
		i = 0;
		old = calloc(sizeof(char ),ft_strlen(cmd)+1);
		x = mini_search(cmd,'=');
		while(i <= x)
		{
			if(cmd[i])
			{
				old[i] = cmd[i];
			}
			i++;
		}
		backup = ft_strjoin_v2(old,ft_strdup(&cmd[x+1]));
		free(list->content);
		list->content = ft_strdup(backup);
		free(backup);
	}
	return j;
}


void	search_varible(char *cmd,t_list *list)
{
	int i;
	int x;
	i = 0;
	x = 0;
	while(list != NULL)
	{
		i = 0;
		while(((char *)list->content)[i])
		{
			if(((char *)list->content)[i] == cmd[i])
			{
				if(((char *)list->content)[i] == 34 || ((char *)list->content)[i])
				{
					x = 1;
					break;
				}
				i++;
			}
			else
				break;
		}
		if(x == 1)
			break;
		list = list->next;
	}
	if(x == 1)
	{
		free(list->content);
		list->content = ft_strdup(cmd);
	}

}

int	mini_checker_export(t_list *list,char *cmd)
{
	int i;
	int x;
	i = 0;
	x = 0;
	while(list != NULL)
	{
		while(cmd[i])
		{
			if(((char *)list->content)[i] && ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if(((char *)list->content)[i] == '=' || ((char *)list->content)[i] == 0)
					x = 1;
			}
			else
			{
				break;
			}
		}
		if(x == 1)
			break;
		list = list->next;
	}
	if(x == 1)
	{
		free(list->content);
		list->content = ft_strdup(cmd);
		return 1;
	}
	return 0;
}

int check_varible_if_have(t_list *list,char *cmd)
{
	int i;
	int x;
	i = 0;
	x = 0;
	while(list != NULL)
	{
		while(cmd[i])
		{
			if(((char *)list->content)[i] && ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if(((char *)list->content)[i] == '=')
					x = 1;
			}
			else
			{
				break;
			}
		}
		if(x == 1)
			break;
		list = list->next;
	}
	if(x == 1)
		return 1;
	return 0;
}

void	print_export(t_list *list)
{
	int i;
	int j;
	i = 0;
	j = 1;
	char *dst;
	while(list != NULL)
	{
		i = 0;
		j = 1;
		dst = (char *)list->content;
		printf("declare -x ");
		while(dst[i])
		{
			if(((char *)list->content)[i] == '=' && j == 1)
			{
				printf("=%c",34);
				j = 0;
			}
			else if(((char *)list->content)[i+1] == '\0' && j == 0)
			{
				printf("%c",((char *)list->content)[i]);
			}
			else
				printf("%c",dst[i]);
			i++;
		}
		if(ft_strchr(list->content,'='))
			printf("%c\n",34);
		else
			printf("\n");
		list = list->next;
	}
}

void	export_command(t_all *my_struct,int c_of_s)
{
	t_list  *ptr = my_struct->list;
    int     i;
    int     print;
    i = 1;
    print = 1;
	while(my_struct->each_cmd[c_of_s].cmd[i])
	{
		if((my_struct->each_cmd[c_of_s].cmd[i][0] == '=' && !my_struct->each_cmd[c_of_s].cmd[i][1]) || my_struct->each_cmd[c_of_s].cmd[i][0] == '=')
		{
			printf("\033[0;31mexport: `%s': not a valid identifier \033[0;37m\n",my_struct->each_cmd[c_of_s].cmd[i]);
		}
		else if(mini_check_export(my_struct->each_cmd[c_of_s].cmd[i]) == 1)
		{
			printf("export: `%s': not a valid identifier\n",my_struct->each_cmd[c_of_s].cmd[i]);
			print = 0;
			break;
		}
		else if(my_struct->each_cmd[c_of_s].cmd[i][ft_strlen(my_struct->each_cmd[c_of_s].cmd[i])-1] != '=' && ft_strchr(my_struct->each_cmd[c_of_s].cmd[i],'=') && my_struct->each_cmd[c_of_s].cmd[i] && !duplicate_check_export(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i]))
		{
			string_dakche(my_struct->list);
			if(replace_varible(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i]) == 0)
			{
				add_node_back(my_struct->each_cmd[c_of_s].cmd[i],&my_struct->list);
			}

		}
		else if(my_struct->each_cmd[c_of_s].cmd[i][ft_strlen(my_struct->each_cmd[c_of_s].cmd[i])-1] == '=' && !duplicate_check_export(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i]))
		{
			if(mini_checker_export(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i]) == 0)
				add_node_back(my_struct->each_cmd[c_of_s].cmd[i],&my_struct->list);
		}
		else if(!ft_strchr(my_struct->each_cmd[c_of_s].cmd[i],'=' && !duplicate_check_export(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i])) && check_varible_if_have(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i]) == 0)
		{
			add_node_back(my_struct->each_cmd[c_of_s].cmd[i],&my_struct->list);
		}
		i++;
	}
	if(print == 1 && !my_struct->each_cmd[c_of_s].cmd[1])
	{
		print_export(my_struct->list);
	}
	my_struct->list = ptr;
}

void	env_command(t_list *list)
{

	while(list != NULL)
	{
		if(mini_search(list->content,61) != 0)
			printf("%s\n",list->content);
		list = list->next;
	}
}
void unset_checker(t_list *list,char *cmd, t_list *head)
{
	int i;
	int x;
	i = 0;
	x = 0;
	while(list != NULL)
	{
		while(cmd[i])
		{
			if(((char *)list->content)[i] && ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if(((char *)list->content)[i] == '=' || ((char *)list->content)[i] == 0)
					x = 1;
			}
			else
			{
				break;
			}
		}
		if(x == 1)
			break;
		list = list->next;
	}
	if(x == 1)
	{
		t_list *back;
		
		back = head;
		while (back)
		{
			if (back->next->content == list->content)
				break;
			back = back->next;
		}
		free(list->content);
		back->next = list->next;
	}
}

void	unset_command(t_all *my_struct,int c_of_s)
{
	t_list  *ptr = my_struct->list;

	int i;
	i = 0;
	while(my_struct->each_cmd[c_of_s].cmd[i])
	{
		unset_checker(my_struct->list,my_struct->each_cmd[c_of_s].cmd[i], ptr);
		i++;

	}
	my_struct->list = ptr;
}

void	exicut_commande(t_all *my_struct, int i, int c_of_s)
{
	if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen("cd")+1))
		exit(1);
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
	{
		exicut_echo(my_struct,c_of_s);
	}
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		export_command(my_struct,c_of_s);
	}
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(my_struct->list);
	}
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(my_struct,c_of_s);
	}
	else if (!ft_strncmp(my_struct->cmd, my_struct->cmd,ft_strlen(my_struct->cmd)))
	{
		check_rediractions(my_struct, c_of_s);
		execve(my_struct->my_path[i], my_struct->each_cmd[c_of_s].cmd, NULL);
	}
}