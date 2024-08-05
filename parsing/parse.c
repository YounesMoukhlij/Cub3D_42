/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/04 16:07:31 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

char	*fix_the_map(char *s, int i, int flag, int j)
{
	char	*str;
	char	*tmp;

	tmp = ft_strtrim(s, " ");
	while (tmp[i++])
	{
		if (tmp[i] == 32 || tmp[i] == 9)
			flag = 0x1;
	}
	if (flag == 0x1)
	{
		i = 0x0;
		str = ft_calloc(0x1, ft_strlen(s) + 0x1);
		if (!str)
			return (NULL);
		while (tmp[i++])
		{
			if (!(tmp[i] == 32 || tmp[i] == 9))
				str[j++] = tmp[i];
		}
	}
	if (flag)
		return (str);
	return (tmp);
}

int	get_length_heigth(char **str, int mode, int i)
{
	if (!mode)
	{
		while (str[i])
			i++;
		i -= 6;
	}
	if (mode)
	{
		while (str[mode][i])
			i++;
	}
	return (i);
}


char	**final_map(t_cube *game, char **str)
{
	int		i;
	int		j;
	char	**s;

	i = 0x0;
	s = (char **)ft_malloc((game->real_map_heigth + 0x1) * 8, 1);
	if (!s)
		return (NULL);
	j = 0x0;
	while (str[i])
	{
		if (i > 0x5)
		{
			s[j] = fill_chars(game, str[i]);
			if (!s[j++])
				return (NULL);
		}
		i++;
	}
	s[j] = 0;
	return (s);
}

mlx_image_t *open_image(char *path, t_cube *game)
{
	mlx_image_t *img;
	mlx_texture_t *texture;

	texture = mlx_load_png(path);
	if (!texture)
	{
		puts("error\n");
		exit(1);
	}
	img = mlx_texture_to_image(game->mlx, texture);
	if (!img)
	{
		exit (0);	
	}
	free(texture);
	return (img);
}

void	ft_load_textures(t_cube *game)
{
	// game->png = malloc(sizeof(t_png));
	// if (!game->png)
	// 	error_message(game, 0x3);

	game->png.ea = open_image(game->texture_walls.ea, game);
	game->png.so = open_image(game->texture_walls.so, game);
	game->png.no = open_image(game->texture_walls.no, game);
	game->png.we = open_image(game->texture_walls.we, game);
	game->png.arm = open_image("./assets/arm.png", game);
	game->png._1 = open_image("./assets/1.png", game);
	game->png._2 = open_image("./assets/2.png", game);
	game->png._3 = open_image("./assets/3.png", game);
	game->png._4 = open_image("./assets/4.png", game);
	game->png._5 = open_image("./assets/5.png", game);
	if (!(game->png.ea || game->png.no || game->png.so || game->png.we))
		error_message(game, 0x3);
}



void	parse(int ac, char *file, t_cube *game)
{
	if (ac <= 1 || ac >= 3)
		error_message(game, 0x1);
	if (check_extension(file) == 0)
		error_message(game, 0x2);
	game->map_2d = read_map_from_file(file, 0x0, 0x0);
	if (!game->map_2d)
		error_message(game, 0x3);
	init_counter(game);
	heigth_width(game);
	check_texture_intra(game, 0x0);
	check_valid_members(game, 0x0, 0x0);
	player_vision(game->map_2d, game);
	parse_entry(game, 0x0);
	ft_load_textures(game);
	game->map = final_map(game, game->map_2d);
	// game->final_map = get_final_map(game, game->map);
	
	// if (!game->texture)
	// {
	// 	puts("eeee\n");
	// 	exit(1);
	// }
	

	// int i = 0;
	// puts("\n\n\n\033[32m --->< THE MAP ><---\033[0m\n\n");
	// while (game->map[i])
	// {
	// 	printf("------------->   [%s]\n", game->map[i]);
	// 	i++;
	// }
}
