/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:37:43 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/04 11:56:50 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	count = 0;
	i = 0;
	in_word = 0;
	while (s[i])
	{
		if (in_word == 1 && s[i] == c)
		{
				in_word = 0;
				count++;
		}
		else if (in_word == 0 && s[i] != c)
				in_word = 1;
		i++;
	}
	if (in_word == 1)
		count++;
	return (count);
}

static void	assign_words(char **result, char const *s, char c, int n_words)
{
	int	index_result;
	int	i;
	int	j;

	i = 0;
	index_result = 0;
	while (index_result < n_words)
	{
		while (s[i] == c)
			i++;
		j = 0;
		while (s[i] != c && s[i])
			result[index_result][j++] = s[i++];
		result[index_result][j] = '\0';
		index_result++;
	}
	result[index_result] = 0;
}

static void	mallocfail(char **result, int i)
{
	i--;
	while (i >= 0)
		free(result[i--]);
}

char	**ft_split(char const *s, char c)
{
	int		n_words;
	int		i;
	char	**result;

	if (s == 0)
		return (0);
	n_words = count_words(s, c);
	result = (char **)malloc(sizeof (char *) * (n_words + 1));
	if (result == 0)
		return (NULL);
	i = 0;
	while (i < n_words)
	{
		result[i] = (char *)malloc(sizeof (char) * (ft_strlen(s) + 1));
		if (result[i] == 0)
		{
			mallocfail(result, i);
			free(result);
			return (NULL);
		}
		i++;
	}
	assign_words(result, s, c, n_words);
	return (result);
}

