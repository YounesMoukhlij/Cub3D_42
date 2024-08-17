/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:07:38 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 10:12:31 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	{
		if (ft_strlen(str[i]) >= 2 && ft_atoi(str[i]) == 0)
			error_message(game, 0x7);
		if (ft_strlen(str[i]) > 3)
			error_message(game, 0x7);
		i++;
	}
	return (0x0);
}

void	parse_s(t_cube *game, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',' && s[i + 1] == ',' && s[i + 1])
			error_message(game, 0x7);
		if (s[ft_strlen(s) - 1] == ',')
			error_message(game, 0x7);
		i++;
	}
}

void	get_path(t_cube *game, int i, char *str)
{
	char	*s;

	s = ft_substr(game->map_2d[i], 3, ft_strlen(game->map_2d[i]) - 1);
	if (!s)
		return ;
	if (!ft_strcmp(str, "NO"))
		game->texture_walls.no = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "SO"))
		game->texture_walls.so = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "EA"))
		game->texture_walls.ea = ft_strtrim(ft_strdup(s), " ");
	else if (!ft_strcmp(str, "WE"))
		game->texture_walls.we = ft_strtrim(ft_strdup(s), " ");
}
