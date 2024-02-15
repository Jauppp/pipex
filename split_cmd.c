/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 09:35:46 by cdomet-d          #+#    #+#             */
/*   Updated: 2024/02/15 17:44:22 by cdomet-d         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*allocword(const char *s, char sep, size_t j)
{
	size_t		len;
	size_t		start_current_word;
	char		*word;

	len = 0;
	start_current_word = j;
	while (s[j] && s[j++] != sep)
		len++;
	word = ft_calloc(len + 1, sizeof (char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start_current_word, len + 1);
	return (word);
}

static void	*freeall(char **arr)
{
	size_t	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (NULL);
}

char	**split_cmd(char const *s, char c)
{
	bool	found_quote;
	char	quote;
	size_t	i;
	size_t	j;
	size_t	nb_words;
	char	**arr;

	i = 0;
	found_quote = false;
	if (!s || !s[i])
		return (NULL);
	nb_words = count_words(s, c);
	arr = ft_calloc(nb_words + 1, sizeof (char *));
	if (!arr)
		return (arr);
	arr[nb_words] = NULL;
	j = 0;
	while (i < nb_words)
	{
		if (s[j] == c)
			j++;
		if (s[j] == DQUOTE || s[j] == SQUOTE)
		{
			quote = s[j];
			found_quote = true;
			j++;
		}
		if (found_quote == true)
		{
			arr[i] = allocword(s, quote, j);
			if (!arr[i])
				return (freeall(arr));
			j += ft_strlen(arr[i]);
			if (s[j] == DQUOTE || s[j] == SQUOTE)
				j++;
			i++;
		}
		if (!s[j])
			break ;
		arr[i] = allocword(s, c, j);
		if (!arr[i])
			return (freeall(arr));
		j += ft_strlen(arr[i]);
		i++;
	}
	return (arr);
}

