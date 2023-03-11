/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:24:10 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/11 15:24:12 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char *args[] = {"env", NULL};
    char *envp[] = {NULL};
    
    if (execve("/usr/bin/env", args, envp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}
