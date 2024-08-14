/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/13 16:43:59 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_test(t_cube *game)
{
	int i = 0;
	while(i < 1000)
	{
		int j = 0;
		while(j < 1500)
		{
			mlx_put_pixel(game->img, j  , i, ft_color(0, 0, 0, 255));
			j++; 
		}
		i++;
	}
}

void	ft_check_move(void *tmp)
{
	double	x;
	double	y;
	t_cube	*game;

	game = (t_cube *)tmp;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation_angle += 1 * rotation_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx,
			MLX_KEY_UP))
	{
		game->move = 1 * player_speed;
		x = sin(game->rotation_angle) * game->move;
		y = cos(game->rotation_angle) * game->move;
		if (check_colesion(game, y + game->player_y, game->player_x + x))
		{
			game->player_y += y;
			game->player_x += x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->rotation_angle += -1 * rotation_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx,
			MLX_KEY_DOWN))
	{
		game->move = -1 * player_speed;
		x = sin(game->rotation_angle) * game->move;
		y = cos(game->rotation_angle) * game->move;
		if (check_colesion(game, game->player_y + y, game->player_x + x))
		{
			game->player_y += y;
			game->player_x += x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		x = player_speed * sin(game->rotation_angle + (90 * (PI / 180)));
		y = player_speed * cos(game->rotation_angle + (90 * (PI / 180)));
		if (check_colesion(game, game->player_y + y, game->player_x + x))
		{
			game->player_y += y;
			game->player_x += x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		x = player_speed * sin(game->rotation_angle - (90 * (PI / 180)));
		y = player_speed * cos(game->rotation_angle - (90 * (PI / 180)));
		if (check_colesion(game, game->player_y + y, game->player_x + x))
		{
			game->player_y += y;
			game->player_x += x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	// ft_test(game);
	ft_drawing_map(game);
	draw_line_DDA(game);
}

void	init_image(t_cube *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEITH);
	game->img_mini_map = mlx_new_image(game->mlx, 200, 200);
	game->mini_heigth = WINDOW_HEITH / 4;
	game->mini_width = WINDOW_WIDTH / 4;
	game->player_turn = 0;
	game->player_walk = 0;
	game->map_widht = game->real_map_width * BOX_SIZE;
	game->map_height = (game->real_map_heigth - 1) * BOX_SIZE;
	game->fov_angle = 60 * (PI / 180);
	game->num_ray = (1500);
}

int	main(int ac, char **av)
{
	t_cube	game;

	game.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEITH, "cub3D", 0);
	parse(ac, av[0x1], &game);
	init_image(&game);
	ft_get_player_position(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.img_mini_map, 0, 0);
	mlx_loop_hook(game.mlx, ft_check_move, &game);
	mlx_loop(game.mlx);
	return (0x0);
}
