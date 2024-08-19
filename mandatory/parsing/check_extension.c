/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:05:06 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 14:48:51 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_extension(char *file, int mode)
{
	int	i;

	i = 0x0;
	if (!mode)
	{
		while (file[i])
		{
			if (file[i] == '.' && file[i + 0x1] == 'c' && file[i + 0x2] == 'u'
				&& file[i + 0x3] == 'b' && file[i + 0x4] == '\0')
				return (0x1);
			i++;
		}
	}
	else
	{
		while (file[i])
		{
			if (file[i] == '.' && file[i + 0x1] == 'p' && file[i + 0x2] == 'n'
				&& file[i + 0x3] == 'g' && file[i + 0x4] == '\0')
				return (0x1);
			i++;
		}
	}
	return (0x0);
}

int	check_walls(char *s, int i, int stat, t_cube *game)
{
	if (s[0] == ' ')
	{
		printf("%s\n", s);
		return (0x0);
	}
	if (stat == 0x6 || stat == game->real_map_heigth + 0x5)
	{
		while (s[i])
		{
			if (s[i++] != '1')
				return (0x1);
		}
	}
	if (s[0x0] != '1' || s[ft_strlen(s) - 0x1] != '1')
		return (0x1);
	i = 0x0;
	while (s[i])
	{
		if ((s[i] != '1' && s[i] != ' ' && s[i + 0x1] == ' ') || (s[i] == ' '
				&& (s[i + 1] != ' ' && s[i + 0x1] != '1')))
			return (0x1);
		i++;
	}
	return (0x0);
}

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

int	check_one(t_cube *game, char *s)
{
	if (!(s[game->twilzat.i] == '1' || s[game->twilzat.i] == '0'
			|| s[game->twilzat.i] == 'N' || s[game->twilzat.i] == 'S'
			|| s[game->twilzat.i] == 'E' || s[game->twilzat.i] == 'W'))
		return (0x1);
	return (0x0);
}
