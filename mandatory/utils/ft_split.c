/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:13:44 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 13:06:19 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_strlen_word(char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int	count_words(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
			i++;
		while (*s && *s != c)
			s++;
	}
	return (i);
}

char	*ft_create(char *s, char c)
{
	char	*r;
	int		len;
	int		i;

	len = ft_strlen_word(s, c);
	i = 0;
	r = (char *)ft_malloc(sizeof(char) * (len + 1), 1);
	if (r == NULL)
		return (NULL);
	while (i < len)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	**r;

	i = 0;
	r = (char **)ft_malloc(sizeof(char *) * ((count_words(s, c) + 1)), 1);
	if (!r)
		return (0);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			r[i] = ft_create(s, c);
			if (!r[i++])
				return (ft_free(r), NULL);
		}
		while (*s && *s != c)
			s++;
	}
	r[i] = 0;
	return (r);
}
