/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 16:09:39 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	show(void)
{
	system("leaks Cub3D_bonus");
}

int	main(int ac, char **av)
{
	t_cube	game;

	// atexit(show);
	game.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEITH, "cub3D", 0);
	parse(ac, av[0x1], &game);
	init_image(&game);
	ft_get_player_position(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.img_mini_map, 0, 0);
	mlx_loop_hook(game.mlx, ft_check_move, &game);
	mlx_loop_hook(game.mlx, ft_handle_mouse, &game);
	mlx_loop(game.mlx);
	ft_malloc(0x0, 0x0);
	return (0x0);
}
