/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/26 17:25:49 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h" // libft
# include <unistd.h> // standard
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
#include <stdio.h>

# define DQUOTE 34
# define SQUOTE 39

typedef struct s_var
{
	char	**paths;
	char	**args;
	char	*apath;
	int		fd[2];
	int		id[2];
	int		i;
}	t_var;

/* Display | TO DELETE */
void	display_tab(char **tab, char *str);

/* Errors */
void	print_error(int error_code, char *error_message);

/* Utils */
void	init_var(t_var	*var);
void	tokenize(char *str);
void	reverse_tokenize(char **tab);
char	*append_cmd(char const *s1, char const *s2);
size_t	count_words(const char *s, char c);

/* Init args */
void	fetch_path(char **envp, t_var *var);
void	find_absolute_path(t_var *var);
void	fetch_args(char **argv, t_var *var);

/* Memory */
void	free_var(t_var *var, int exit_code, char *error_message);
void	free_dtab(char **dtab);
void	reinit(char *temp);

#endif