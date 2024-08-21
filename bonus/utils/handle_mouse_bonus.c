/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:35:46 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 17:55:14 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	ft_handle_mouse(void *param)
{
	t_cube	*game;
	int		x;
	int		y;

	game = (void *)param;
	if (game->mouse_stat == 1)
	{
		mlx_get_mouse_pos(game->mlx, &x, &y);
		game->rotation_angle += game->mouse_speed * (x - (WINDOW_WIDTH / 2));
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
	}
}
