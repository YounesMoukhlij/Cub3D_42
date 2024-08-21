/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:05:49 by abechcha          #+#    #+#             */
/*   Updated: 2024/08/18 16:05:51 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	parse_entry(t_cube *game, int i)
{
	char	*s1;
	char	*s2;

	while (game->map_2d[i] && i < 6)
	{
		s1 = check_chars(ft_substr(ft_strtrim(game->map_2d[i], " "), 0x0, 2));
		if (!s1)
			error_message(game, 10);
		if (!ft_strcmp(s1, "C ") || !ft_strcmp(s1, "F "))
		{
			s2 = ft_substr(ft_strtrim(game->map_2d[i], " "), 0x2,
					ft_strlen(game->map_2d[i]) - 1);
			if (parse_numbers(s2))
				error_message(game, 10);
			if (!ft_strcmp(s1, "C "))
				fill_colors(game, s2, 0);
			else if (!ft_strcmp(s1, "F "))
				fill_colors(game, s2, 1);
		}
		if (!ft_strcmp(s1, "NO") || !ft_strcmp(s1, "SO") || !ft_strcmp(s1, "EA")
			|| !ft_strcmp(s1, "WE"))
			get_path(game, i, s1);
		i++;
	}
}

int	get_length_heigth(char **str, int mode, int i)
{
	if (!mode)
	{
		while (str[i])
			i++;
		i -= 6;
	}
	if (mode)
	{
		while (str[mode][i])
			i++;
	}
	return (i);
}

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

char	**final_map(t_cube *game, char **str)
{
	int		i;
	int		j;
	char	**s;

	i = 0x0;
	s = (char **)ft_malloc((game->real_map_heigth + 0x1) * 8, 1);
	if (!s)
		return (NULL);
	j = 0x0;
	while (str[i])
	{
		if (i > 0x5)
		{
			s[j] = fill_chars(game, str[i]);
			if (!s[j++])
				return (NULL);
		}
		i++;
	}
	s[j] = 0;
	return (ft_maping(game, s, 0));
}
