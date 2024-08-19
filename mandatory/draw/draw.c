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
	else
		mlx_put_pixel(game->img_mini_map, j, i, 0xFFFFFFFF);
	return (0);
}
