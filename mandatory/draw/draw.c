/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:32:30 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 15:17:24 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	casse_la_tete(t_cube *game, int i, int j)
{
	if (!game->map[game->start_y / BOX_MINI][game->start_x
		/ BOX_MINI])
		return (0x1);
	else if (game->map[game->start_y / BOX_MINI][game->start_x
		/ BOX_MINI] == '1')
		mlx_put_pixel(game->img_mini_map, j, i, 0xFF0000FF);
	else if (game->map[game->start_y / BOX_MINI][game->start_x
		/ BOX_MINI] == 'D')
		mlx_put_pixel(game->img_mini_map, j, i, ft_color(0, 255, 0,
				255));
	else
		mlx_put_pixel(game->img_mini_map, j, i, 0xFFFFFFFF);
	return (0);
}

void	check_order(char **s, int i)
{
	while (s[i] && i < 6)
	{
		if (!i && ft_strcmp("NO", ft_substr(s[i], 0, 2)))
			error_message(0x0, 6);
		else if (i == 1 && ft_strcmp("SO", ft_substr(s[i], 0, 2)))
			error_message(0x0, 6);
		else if (i == 2 && ft_strcmp("WE", ft_substr(s[i], 0, 2)))
			error_message(0x0, 6);
		else if (i == 3 && ft_strcmp("EA", ft_substr(s[i], 0, 2)))
			error_message(0x0, 6);
		else if (i == 4 && ft_strcmp("F", ft_substr(s[i], 0, 1)))
			error_message(0x0, 6);
		else if (i == 5 && ft_strcmp("C", ft_substr(s[i], 0, 1)))
			error_message(0x0, 6);
		i++;
	}
}
