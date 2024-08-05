/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:07:38 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/05 16:31:36 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	i = 0x6;
	while (game->map_2d[i] && i > 0x5)
	{
		j = 0x0;
		str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
		if (check_walls(ft_strtrim(game->map_2d[i], " "), 0x0, i, game))
			error_message(game, 0x4);
		while (str[j])
		{
			if (!(str[j] == '0' || str[j] == '1'
				|| str[j] == 'N' || str[j] == 'S'
				|| str[j] == 'W' || str[j] == 'E'))
				error_message(game, 0x4);
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

void	fill_colors(t_cube *game, char *s, int mode)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split(ft_strtrim(s, " "), ',');
	while (str[i])
	{
		if (!mode && !i)
			game->colors.r_c = ft_atoi(str[i]);
		else if (!mode && i == 1)
			game->colors.g_c = ft_atoi(str[i]);
		else if (!mode && i == 2)
			game->colors.b_c = ft_atoi(str[i]);
		else if (mode && !i)
			game->colors.r_f = ft_atoi(str[i]);
		else if (mode && i == 1)
			game->colors.g_f = ft_atoi(str[i]);
		else if (mode && i == 2)
			game->colors.b_f = ft_atoi(str[i]);
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
		game->texture_walls.no = ft_strdup(s);
	else if (!ft_strcmp(str, "SO"))
		game->texture_walls.so = ft_strdup(s);
	else if (!ft_strcmp(str, "EA"))
		game->texture_walls.ea = ft_strdup(s);
	else if (!ft_strcmp(str, "WE"))
		game->texture_walls.we = ft_strdup(s);
}
