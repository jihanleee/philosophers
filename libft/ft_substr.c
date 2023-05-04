/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:16:37 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/04 11:56:50 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == 0)
		return (0);
	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(sizeof (char) * (ft_strlen(s) + 1));
		sub[0] = '\0';
		return (sub);
	}
	if (ft_strlen(s) < len)
		sub = (char *)malloc(sizeof (char) * (ft_strlen(s) + 1));
	else
		sub = (char *)malloc(sizeof (char) * (len + 1));
	if (sub == 0)
		return (NULL);
	i = 0;
	while (i < len && s[i])
	{
		sub[i] = s[(size_t)start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

