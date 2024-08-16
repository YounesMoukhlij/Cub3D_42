/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/15 12:57:43 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void ft_check_move(void *tmp)
{
	double x;
	double y;
	t_cube *game;

	game = (t_cube *)tmp;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation_angle += 1 * rotation_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx,
																 MLX_KEY_UP))
	{
		game->move = 1 * game->player_speed;
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
		game->move = -1 * game->player_speed;
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
		x = game->player_speed * sin(game->rotation_angle + (90 * (PI / 180)));
		y = game->player_speed * cos(game->rotation_angle + (90 * (PI / 180)));
		if (check_colesion(game, game->player_y + y, game->player_x + x))
		{
			game->player_y += y;
			game->player_x += x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		x = game->player_speed * sin(game->rotation_angle - (90 * (PI / 180)));
		y = game->player_speed * cos(game->rotation_angle - (90 * (PI / 180)));
		if (check_colesion(game, game->player_y + y, game->player_x + x))
		{
			game->player_y += y;
			game->player_x += x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_MINUS))
	{
		if (game->player_speed > 0)
			game->player_speed -= 2;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_EQUAL))
		game->player_speed += 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
	{
		if (game->mouse_stat == 1)
			game->mouse_stat = 0;
		else if (game->mouse_stat == 0)
			game->mouse_stat = 1;
	}
	ft_drawing_map(game);
	draw_line_DDA(game);
}

void init_image(t_cube *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEITH);
	game->img_mini_map = mlx_new_image(game->mlx, 200, 200);
	game->mini_heigth = WINDOW_HEITH / 4;
	game->mini_width = WINDOW_WIDTH / 4;
	game->player_turn = 0;
	game->player_walk = 0;
	game->map_widht = game->real_map_width * BOX_SIZE;
	game->map_height = (game->real_map_heigth - 1) * BOX_SIZE;
	game->field_of_view_angle = 120 * (PI / 180);
	game->num_ray = (WINDOW_WIDTH);
	game->mouse_stat = 0;
	game->player_speed = 60;
}

void ft_handle_mouse(void *param)
{
	t_cube *game;
	int x;
	int y;

	game = (void *)param;
	if (game->mouse_stat == 1)
	{
		mlx_get_mouse_pos(game->mlx, &x, &y);
		game->rotation_angle += mouse_speed * (x - (WINDOW_WIDTH / 2));
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
		mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEITH / 2);
	}
}

int main(int ac, char **av)
{
	t_cube game;

	game.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEITH, "cub3D", 0);
	parse(ac, av[0x1], &game);
	init_image(&game);
	ft_get_player_position(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.img_mini_map, 0, 0);
	mlx_loop_hook(game.mlx, ft_check_move, &game);
	mlx_loop_hook(game.mlx, ft_handle_mouse, &game);
	mlx_loop(game.mlx);
	return (0x0);
}
