/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:33:44 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 17:55:14 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	extra_one(t_cube *game, double *x, double *y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation_angle += 1 * game->rotation_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx,
			MLX_KEY_UP))
	{
		game->move = 1 * game->player_speed;
		*x = sin(game->rotation_angle) * game->move;
		*y = cos(game->rotation_angle) * game->move;
		if (check_colesion(game, *y + game->player_y, game->player_x + *x))
		{
			game->player_y += *y;
			game->player_x += *x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->rotation_angle += -1 * game->rotation_speed;
}

void	extra_two(t_cube *game, double *x, double *y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx,
			MLX_KEY_DOWN))
	{
		game->move = -1 * game->player_speed;
		*x = sin(game->rotation_angle) * game->move;
		*y = cos(game->rotation_angle) * game->move;
		if (check_colesion(game, game->player_y + *y, game->player_x + *x))
		{
			game->player_y += *y;
			game->player_x += *x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*x = game->player_speed * sin(game->rotation_angle + (90 * (PI / 180)));
		*y = game->player_speed * cos(game->rotation_angle + (90 * (PI / 180)));
		if (check_colesion(game, game->player_y + *y, game->player_x + *x))
		{
			game->player_y += *y;
			game->player_x += *x;
		}
	}
}

void	extra_tree(t_cube *game, double *x, double *y)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*x = game->player_speed * sin(game->rotation_angle - (90 * (PI / 180)));
		*y = game->player_speed * cos(game->rotation_angle - (90 * (PI / 180)));
		if (check_colesion(game, game->player_y + *y, game->player_x + *x))
		{
			game->player_y += *y;
			game->player_x += *x;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_MINUS))
	{
		if (game->player_speed > 0)
			game->player_speed -= 2;
	}
}

void	ft_check_move(void *tmp)
{
	double	x;
	double	y;
	t_cube	*game;

	game = (t_cube *)tmp;
	extra_one(game, &x, &y);
	extra_two(game, &x, &y);
	extra_tree(game, &x, &y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_EQUAL))
	{
		if (game->player_speed < 100)
			game->player_speed += 2;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
	{
		if (game->mouse_stat == 1)
			game->mouse_stat = 0;
		else if (game->mouse_stat == 0)
			game->mouse_stat = 1;
	}
	ft_drawing_map(game);
	draw_line_dda(game);
}

void	init_image(t_cube *game)
{
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGTH);
	game->img_mini_map = mlx_new_image(game->mlx, 200, 200);
	game->mini_heigth = WINDOW_HEIGTH / 4;
	game->mini_width = WINDOW_WIDTH / 4;
	game->player_turn = 0;
	game->player_walk = 0;
	game->map_widht = game->real_map_width * BOX_SIZE;
	game->map_height = (game->real_map_heigth - 1) * BOX_SIZE;
	game->field_of_view_angle = 60 * (PI / 180);
	game->num_ray = (WINDOW_WIDTH);
	game->mouse_stat = 0;
	game->player_speed = 60;
	game->mouse_speed = 0.04 * (PI / 180);
	game->rotation_speed = 3 * (PI / 180);
	game->extra.dx = 0;
	game->extra.dy = 0;
	game->extra.sx = 0;
	game->extra.sy = 0;
	game->extra.err = 0;
	game->extra.e2 = 0;
}
