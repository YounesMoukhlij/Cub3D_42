/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:51:04 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/03 18:50:02 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void  ft_check_move(void *tmp)
{
	t_cube *game;
	game = (t_cube *)tmp;

	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation_angle += 1 * rotation_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
	{
		game->move = 1 * player_speed;
		if (ft_check_walls( game,game->player_y + cos(game->rotation_angle)  * game->move,  game->player_x + sin(game->rotation_angle) * game->move)){
			game->player_y += cos(game->rotation_angle) * game->move;
			game->player_x += sin(game->rotation_angle) * game->move;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->rotation_angle += -1 * rotation_speed;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
	{
		game->move = -1 * player_speed;
		if (ft_check_walls(game,game->player_y + cos(game->rotation_angle)  * game->move,  game->player_x + sin(game->rotation_angle) * game->move)){
			game->player_y += cos(game->rotation_angle) * game->move;
			game->player_x += sin(game->rotation_angle) * game->move;
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (ft_check_walls(game,game->player_y + cos(game->rotation_angle + rotation_speed), game->player_x + sin(game->rotation_angle + rotation_speed)))
		{
			game->player_y += cos(game->rotation_angle + rotation_speed);
			game->player_x += sin(game->rotation_angle + rotation_speed);
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (ft_check_walls(game ,game->player_y + cos(game->rotation_angle + ( -1 * rotation_speed)), game->player_x + sin(game->rotation_angle +( -1 * rotation_speed))))
		{
			game->player_y += cos(game->rotation_angle + (-1 *rotation_speed));
			game->player_x += sin(game->rotation_angle + (-1 *rotation_speed));
		}
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	ft_test(game);     //// removed before textures
	ft_drawing_map(game);
	draw_line_DDA(game);
}


void	init_image(t_cube *game)
{
	game->img  = mlx_new_image(game->mlx, 1500,1000);
	game->img_mini_map  = mlx_new_image(game->mlx, 200,200);
	game->mini_heigth = WINDOW_HEITH / 4;
	game->mini_width = WINDOW_WIDTH / 4;
	game->player_turn = 0;
	game->player_walk = 0;
	game->map_widht = game->real_map_width * BOX_SIZE;
	game->map_height = (game->real_map_heigth -1 ) * BOX_SIZE;
	game->fov_angle = 60 * (PI / 180);
	game->num_ray = (1500);
}


int main(int ac, char **av)
{
	t_cube	game;

	parse(ac, av[0x1], &game);
	game.mlx =  mlx_init(WINDOW_WIDTH,WINDOW_HEITH, "cub3D", 0);
    ft_get_player_position(&game);
	init_image(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_image_to_window(game.mlx, game.img_mini_map, 0, 0);
	game.img_wall =  mlx_texture_to_image(game.mlx, game.texture);
	ft_drawing_map(&game);
	mlx_loop_hook(game.mlx, ft_check_move , &game);
	mlx_loop(game.mlx);

	return (0x0);
}
