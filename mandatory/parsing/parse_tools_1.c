/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:03:53 by abechcha          #+#    #+#             */
/*   Updated: 2024/08/18 13:13:32 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

mlx_image_t	*open_image(char *path, t_cube *game)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		mlx_delete_texture(texture);
		ft_malloc(0, 0);
		exit(1);
	}
	img = mlx_texture_to_image(game->mlx, texture);
	if (!img)
	{
		mlx_delete_texture(texture);
		ft_malloc(0, 0);
		exit(1);
	}
	mlx_delete_texture(texture);
	return (img);
}

void	ft_load_textures(t_cube *game)
{
	game->png.ea = open_image(game->texture_walls.ea, game);
	game->png.so = open_image(game->texture_walls.so, game);
	game->png.no = open_image(game->texture_walls.no, game);
	game->png.we = open_image(game->texture_walls.we, game);
	game->png._1 = open_image("./assets/1.png", game);
	game->png._2 = open_image("./assets/2.png", game);
	game->png._3 = open_image("./assets/3.png", game);
	game->png._4 = open_image("./assets/4.png", game);
	game->png._5 = open_image("./assets/5.png", game);
	if (!game->png.ea || !game->png.no || !game->png.so || !game->png.we
		|| !game->png._1 || !game->png._2 || !game->png._3
		|| !game->png._4 || !game->png._5)
		error_message(game, 0x6);
}

void	check_textures(t_cube *game)
{
	if (!check_extension(game->texture_walls.ea, 0x1)
		|| !check_extension(game->texture_walls.we, 0x1)
		|| !check_extension(game->texture_walls.no, 0x1)
		|| !check_extension(game->texture_walls.so, 0x1))
		error_message(game, 0x2);
}

void	check_player(t_cube *game, char **s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == 'N')
				game->parse_p.n++;
			else if (s[i][j] == 'E')
				game->parse_p.e++;
			else if (s[i][j] == 'W')
				game->parse_p.w++;
			else if (s[i][j] == 'S')
				game->parse_p.s++;
			j++;
		}
		i++;
	}
	if (ultra_check(game, 1))
		error_message(game, 9);
}

void	init_counter(t_cube *game)
{
	game->cnt.a1 = 0;
	game->cnt.a2 = 0;
	game->cnt.a3 = 0;
	game->cnt.a4 = 0;
	game->cnt.a5 = 0;
	game->cnt.a6 = 0;
	game->parse_p.n = 0;
	game->parse_p.s = 0;
	game->parse_p.w = 0;
	game->parse_p.e = 0;
}
