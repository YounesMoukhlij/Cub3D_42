/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:05:06 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 11:55:13 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	check_extension(char *file, int mode)
{
	int	i;

	i = 0x0;
	while (file[i] && !mode)
	{
		if (file[i] == '.' && file[i + 0x1] == 'c' && file[i + 0x2] == 'u'
			&& file[i + 0x3] == 'b' && file[i + 0x4] == '\0')
			return (0x1);
		i++;
	}
	while (file[i] && mode)
	{
		if (file[i] == '.' && file[i + 0x1] == 'p' && file[i + 0x2] == 'n'
			&& file[i + 0x3] == 'g' && file[i + 0x4] == '\0')
			return (0x1);
		i++;
	}
	return (0x0);
}

int	check_walls(char *s, int i, int stat, t_cube *game)
{
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

char	*check_chars(char *s)
{
	if (s[0] == 'C')
		if (ft_strcmp(s, "C "))
			return (NULL);
	if (s[0] == 'F')
		if (ft_strcmp(s, "F "))
			return (NULL);
	if (s[0] == 'N')
		if (ft_strcmp(s, "NO"))
			return (NULL);
	if (s[0] == 'S')
		if (ft_strcmp(s, "SO"))
			return (NULL);
	if (s[0] == 'W')
		if (ft_strcmp(s, "WE"))
			return (NULL);
	if (s[0] == 'E')
		if (ft_strcmp(s, "EA"))
			return (NULL);
	return (s);
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
				error_message(game, 0);
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
			|| s[game->twilzat.i] == 'E' || s[game->twilzat.i] == 'W'
			|| s[game->twilzat.i] == 'D'))
		return (0x1);
	return (0x0);
}

char	*fill_chars(t_cube *game, char *s)
{
	game->twilzat.i = 0;
	game->twilzat.j = 0;
	game->twilzat.f = 0;
	if (ft_strlen(s) < game->real_map_width)
		game->twilzat.f = 1;
	if (game->twilzat.f)
	{
		game->twilzat.tmp = ft_malloc(game->real_map_width + 1, 1);
		if (!game->twilzat.tmp)
			return (NULL);
		while (s[game->twilzat.i])
		{
			if (check_one(game, s))
				game->twilzat.tmp[game->twilzat.j] = ' ';
			else
				game->twilzat.tmp[game->twilzat.j] = s[game->twilzat.i];
			game->twilzat.i++;
			game->twilzat.j++;
		}
		game->twilzat.tmp[game->twilzat.j] = '\0';
	}
	if (!game->twilzat.f)
		return (ft_strdup(s));
	return (game->twilzat.tmp);
}
