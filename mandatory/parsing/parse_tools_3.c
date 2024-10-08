/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:32:33 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 14:49:38 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_text(char *s)
{
	if (!ft_strcmp(ft_substr(s, 0x0, 0x2), "NO"))
		return (0x1);
	else if (!ft_strcmp(ft_substr(s, 0x0, 0x2), "SO"))
		return (0x1);
	else if (!ft_strcmp(ft_substr(s, 0x0, 0x2), "WE"))
		return (0x1);
	else if (!ft_strcmp(ft_substr(s, 0x0, 0x2), "EA"))
		return (0x1);
	else if (!ft_strcmp(ft_substr(s, 0x0, 0x2), "C "))
		return (0x1);
	else if (!ft_strcmp(ft_substr(s, 0x0, 0x2), "F "))
		return (0x1);
	return (0x0);
}

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	while (game->map_2d[i] && i > 0x5)
	{
		j = 0x0;
		str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
		if (game->map_2d[i][0] != ' ')
		{
			if (check_walls(ft_strtrim(game->map_2d[i], " "), 0x0, i, game))
			{
				if (check_text(ft_strtrim(game->map_2d[i], " ")))
					error_message(game, 4);
				error_message(game, 8);
			}
		}
		while (str[j])
		{
			if (!(str[j] == '0' || str[j] == '1'
					|| str[j] == 'N' || str[j] == 'S'
					|| str[j] == 'W' || str[j] == 'E'))
				error_message(game, 8);
			j++;
		}
		i++;
	}
}

void	player_vision(char **s, t_cube *game)
{
	int	i;
	int	j;

	i = 6;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == 'N')
				game->rotation_angle = (3 * PI) / 2;
			else if (s[i][j] == 'S')
				game->rotation_angle = PI / 2;
			else if (s[i][j] == 'W')
				game->rotation_angle = PI;
			else if (s[i][j] == 'E')
				game->rotation_angle = 0;
			j++;
		}
		i++;
	}
}

int	check_color(t_cube *game, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > 3)
			error_message(game, 10);
		i++;
	}
	if (i > 3)
		error_message(game, 10);
	return (0x0);
}

void	parse_s(t_cube *game, char *s, int i)
{
	while (s[i])
	{
		if (s[i] == ',' && s[i + 1] == ',' && s[i + 1])
			error_message(game, 10);
		if (s[ft_strlen(s) - 1] == ',')
			error_message(game, 10);
		i++;
	}
}
