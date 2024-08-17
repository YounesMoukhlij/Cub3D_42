/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:32:30 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 17:29:48 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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

void	ft_drawing_map_element(t_cube *game, int i, int j)
{
	game->player_y_mini_map = (game->player_x / BOX_SIZE) * BOX_MINI;
	game->player_x_mini_map = (game->player_y / BOX_SIZE) * BOX_MINI;
	game->start_y = game->player_y_mini_map - 100;
	while (game->start_y < game->player_y_mini_map + 100)
	{
		j = 0;
		game->start_x = game->player_x_mini_map - 100;
		while (game->start_x < game->player_x_mini_map + 100)
		{
			if (check_me(game->start_x, game->start_y,
					game->map_widht, game->map_height))
			{
				if (casse_la_tete(game, i, j))
					break ;
			}
			else
				mlx_put_pixel(game->img_mini_map, j, i,
					ft_color(0, 32, 0, 255));
			game->start_x++;
			j++;
		}
		game->start_y++;
		i++;
	}
}
