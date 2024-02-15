/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/14 17:56:18 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
#include <stdio.h>


typedef struct s_process
{
	int	p1;
	int	p2;
}	t_proc;

typedef struct s_var
{
	char	**path;
	char	*a_path;
	char	*cmd_1;
	char	*cmd_2;
	char	*file_1;
	char	*file_2;
}	t_var;

/* Handle error */
void	print_error(int error_code, char *error_message);

/* Handle arguments */
void	fetch_path(char **envp, t_var *var);
void	find_absolute_path(t_var *var);
char	*fetch_cmd_1(char **argv, int arg);

/* Handle memory */
void	free_dtab(char **dtab);
void	free_var(t_var *var, int exit_code, char *error_message);

/* Utils */
void	init_var(t_var	*var);
void	display_tab(char **tab);
char	*append_cmd(char const *s1, char const *s2);

#endif