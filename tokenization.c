/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:46:42 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/16 12:47:10 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	tokenize(char *str)
{
	size_t	i;
	bool	quote;
	char	c;

	i = 0;
	quote = false;
	while (str[i])
	{
		if (quote == false && (str[i] == DQUOTE || str[i] == SQUOTE))
		{
			quote = true;
			c = str[i];
			i++;
		}
		if (quote == true && str[i] == ' ')
			str[i] = str[i] * -1;
		if (quote == true && str[i] == c)
			quote = false;
		i++;
	}
}

void	reverse_tokenize(char **tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] < 0)
				tab[i][j] = tab[i][j] * -1;
			j++;
		}
		i++;
	}
}
