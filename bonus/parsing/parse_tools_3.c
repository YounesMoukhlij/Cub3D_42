/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:32:33 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 15:27:08 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	i = 0x6;
	while (game->map_2d[i] && i > 0x5)
	{
		j = 0x0;
		str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
		if (check_walls(ft_strtrim(game->map_2d[i], " "), 0x0, i, game))
			error_message(game, 8);
		while (str[j])
		{
			if (str[j] == 'D')
				game->found_door = 1;
			if (!(str[j] == '0' || str[j] == '1' || str[j] == 'D'
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

int	parse_numbers(char *s)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = ft_split(ft_strtrim(s, " "), ',');
	if (!str)
		return (1);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
				return (1);
			j++;
		}
		if (ft_atoi(str[i]) > 255 || ft_atoi(str[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_color(t_cube *game, char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
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
