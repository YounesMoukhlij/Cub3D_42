/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:03:13 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/21 11:03:48 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	check_set(char s, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*r;
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (check_set(*s1, set) == 1)
			s1++;
		else
			break ;
	}
	len = ft_strlen(s1);
	while (len)
	{
		if (check_set(s1[len - 1], set) == 1)
			len--;
		else
			break ;
	}
	r = ft_malloc(sizeof(char) * (len + 1), 1);
	if (!r)
		return (0);
	ft_strlcpy(r, s1, len + 1);
	return (r);
}
