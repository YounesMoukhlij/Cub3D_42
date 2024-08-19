/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:06:27 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 14:35:38 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_texture_intra(t_cube *game, int i)
{
	char	*str;

	while (game->map_2d[i] && i < 0x6)
	{
		str = ft_substr(game->map_2d[i], 0x0, 2);
		if (!ft_strcmp(str, "NO"))
			game->cnt.a1++;
		else if (!ft_strcmp(str, "SO"))
			game->cnt.a2++;
		else if (!ft_strcmp(str, "EA"))
			game->cnt.a3++;
		else if (!ft_strcmp(str, "C "))
			game->cnt.a4++;
		else if (!ft_strcmp(str, "F "))
			game->cnt.a5++;
		else if (!ft_strcmp(str, "WE"))
			game->cnt.a6++;
		i++;
	}
	if (ultra_check(game, 0))
		error_message(game, 0x4);
}

void	init_counter(t_cube *game)
{
	game->cnt.a1 = 0;
	game->cnt.a2 = 0;
	game->cnt.a3 = 0;
	game->cnt.a4 = 0;
	game->cnt.a5 = 0;
	game->cnt.a6 = 0;
	game->parse_p.n = 0;
	game->parse_p.s = 0;
	game->parse_p.w = 0;
	game->parse_p.e = 0;
}

int	ft_strlen_ii(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != 9)
			len++;
		i++;
	}
	return (len);
}

void	heigth_width(t_cube *game)
{
	int	i;
	int	j;

	i = 6;
	j = 0;
	while (game->map_2d[i])
	{
		if (j <= ft_strlen_ii(game->map_2d[i]))
			j = ft_strlen_ii(game->map_2d[i]);
		i++;
	}
	game->real_map_width = j;
	game->real_map_heigth = get_length_heigth(game->map_2d, 0, 6);
}

int	player_num(t_cube *game)
{
	if ((game->parse_p.n + game->parse_p.s
			+ game->parse_p.w + game->parse_p.e) == 0x0)
		return (0x1);
	if ((game->parse_p.n + game->parse_p.e
			+ game->parse_p.w + game->parse_p.s) > 0x1)
		return (0x1);
	if (game->parse_p.n > 0x1
		|| game->parse_p.e > 0x1
		|| game->parse_p.w > 0x1
		|| game->parse_p.s > 0x1)
		return (0x1);
	if (game->parse_p.n != 0)
		game->player_vision = 1;
	else if (game->parse_p.s != 0)
		game->player_vision = 2;
	else if (game->parse_p.w != 0)
		game->player_vision = 3;
	else if (game->parse_p.e != 0)
		game->player_vision = 4;
	return (0x0);
}
