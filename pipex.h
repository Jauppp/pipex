/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:02:04 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/03/07 14:46:20 by cdomet-d         ###   ########lyon.fr   */
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

# define DQUOTE 34
# define SQUOTE 39
# define R	0
# define W	1

typedef struct s_v
{
	char	**args; // current command arguments
	char	**paths; // env paths
	char	*a_path; // absolute path for the current command
	int		ac; // number of arguments given to pipex
	int		fd[2];
	int		file[2];
	int		i;
	int		id;
	int		tmp_in;
}	t_var;

/* Display | TO DELETE */
void	display_tab(char **tab, char *str);
void	display_t_var(t_var v);
void	display_fds(t_var v);

/* Errors */
void	print_error(int error_code, char *error_message);

/* Utils */
char	*append_cmd(char const *s1, char const *s2);
void	init_var(t_var	*v, int argc);
void	reverse_tokenize(char **tab);
void	tokenize(char *str);

/* Init args */
int		fetch_a_path(char *argv[], t_var *v);
void	fetch_args(char **argv, t_var *v);
void	fetch_files(char **argv, t_var *v);
void	fetch_path(char **envp, t_var *v);

/* Memory */
void	free_v(t_var *v, int exit_code, char *error_message);
void	free_dtab(char **dtab);
void	reinit(char *temp);

/* Exec_cmd */
void	fork_and_exec(t_var *v, char *argv[]);
void	exec_first_cmd(t_var *v);
void	exec_last_cmd(t_var *v);
void	exec_cmd(t_var *v);

#endif