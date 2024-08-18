/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:11:09 by abechcha          #+#    #+#             */
/*   Updated: 2024/08/17 10:13:31 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	fill_colors(t_cube *game, char *s, int mode)
{
	char	**str;
	int		i;

	i = 0;
	parse_s(game, s);
	str = ft_split(ft_strtrim(s, " "), ',');
	if (!str)
		return ;
	check_color(game, str);
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

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	i = 0x6;
	while (game->map_2d[i] && i > 0x5)
	{
		j = 0x0;
		str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
		if (check_walls(ft_strtrim(game->map_2d[i], " "), 0x0, i, game))
			error_message(game, 200);
		while (str[j])
		{
			if (!(str[j] == '0' || str[j] == '1' || str[j] == 'D'
					|| str[j] == 'N' || str[j] == 'S' || str[j] == 'W'
					|| str[j] == 'E'))
				error_message(game, 0x4);
			j++;
		}
		i++;
	}
}
