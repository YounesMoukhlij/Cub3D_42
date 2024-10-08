/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 18:49:44 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 11:45:38 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_check_sprit(t_cube *game, int next_horizontal_x, int next_horizontal_y)
{
	if (next_horizontal_y / BOX_SIZE > game->map_widht || next_horizontal_x
		/ BOX_SIZE > game->map_height)
		return (0);
	if (game->map[(next_horizontal_y / BOX_SIZE)][(next_horizontal_x
			/ BOX_SIZE)] == 'C')
		return (1);
	return (0);
}

int	ft_check_door(t_cube *game, int next_horizontal_x, int next_horizontal_y)
{
	int	y;
	int	x;

	y = next_horizontal_y - (int)game->player_x;
	x = next_horizontal_x - (int)game->player_y;
	x = abs(x);
	y = abs(y);
	if (next_horizontal_y / BOX_SIZE > game->map_widht || next_horizontal_x
		/ BOX_SIZE > game->map_height)
		return (0);
	if ((game->map[(next_horizontal_y / BOX_SIZE)][(next_horizontal_x
				/ BOX_SIZE)] == 'D' && (x > BOX_SIZE / 2 || y > BOX_SIZE / 2)))
		return (1);
	return (0);
}
