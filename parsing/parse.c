/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/05 14:01:30 by youmoukh         ###   ########.fr       */
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
	s = (char **)malloc((game->real_map_heigth + 0x1) * 8);
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
		error_message(game, 0x1);
	img = mlx_texture_to_image(game->mlx, texture);
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
	if (!(game->png.ea || game->png.no || game->png.so || game->png.we))
		error_message(game, 0x3);
}

// int	check_is_single_map(char *s)
// {
// 	int i = 0;

// 	puts("pp\n");
// 	while (s[i])
// 	{
// 		if (s[i] == '1' && s[i] == ' ')
// 		{
// 			while (s[i] == ' ' && s[i])
// 			{
// 				if (s[i] == '1')
// 				{
// 					puts("AMAMAM HERE\n");
// 					break ;
// 				}
// 				i++;
// 			}
// 			puts("YOYOYOYOYOY");
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void pos_player(char **s, int *pos_x, int *pos_y)
{
	int i = 0;
	int  j = 0;


	while (s[j])
	{
		i = 0;
		while (s[j][i])
		{
			if (s[j][i] == 'N' || s[j][i] == 'S' | s[j][i] == 'E' || s[j][i] == 'W')
			{
				*pos_x = i;
				*pos_y = j;
				return ;
			}
			i++;
		}
		j++;
	}
}


int ch_wll(char *s)
{
	int i = 0;

	// printf("--->[%s]\n" ,s/ );
	while (s[i])
	{
		if (s[i] == '1' && s[i + 1] == ' ')
		{
			// puts("!");
			while (s[i] == ' ' && s[i])
			{
				// puts("2");
				if (s[i + 1] == '1')
				{
					// puts("3");
					while (s[i] && s[i] == '1')
					{
						// puts("4");
						if (s[i] == '\0')
							return (1);
						i++;
					}
				}
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	check_me(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == '1' && s[i + 1] == ' ' && s[i + 1] && s[i] )
		{
			while (s[i] == ' ' && s[i])
			{
				puts("111111111111212121212");
				i++;
			}
			// while ((s[i] == '1' || s[i] == '0' || s[i] == 'N') && s[i])
			// {
			// 	// puts("???????????????????????");
			// 	i++;
			// }
			printf("~~~~~~[%d]\n", i);
			// // if (i == ft_strlen(s) - 1)
			// if (!s[i])
			// {
			// 	puts("MOUHKJJJJ");
			// 	return (1);
			// }
		}
		i++;
	}
	return (0);
}

void	back_track(t_cube *game, char **s, int pos_x, int pos_y)
{
	(void) game;
	// int i = 0;
	int inc = pos_y;
	int first_wall = 0;
	(void) pos_x;
	(void) pos_y;
	printf("pos_x-->[%d]\n", pos_x);
	printf("pos_y-->[%d]\n", pos_y);
		// while (inc > 0)
		// {
		// // printf("-->%d\n", inc);
		// 	printf("[%s]\n", s[inc]);
		// 	// puts("HERE\n");
		// 	first_wall = ch_wll(s[inc]);
		// 	inc--;
		// }
		inc = pos_y;
		printf("\n\n\n\n");
		while (s[inc])
		{
			if (check_me(s[inc]))
			{
				puts("YOUNES\n");
				break ;
			}
				
			// printf("[%s]\n", s[inc]);
			// first_wall = ch_wll(s[inc]);
			inc++;
		}
		printf("~~~[%d]\n", first_wall);
		// while (inc < 0)
}

char	**get_final_map(t_cube *game, char **s, int i, int j)
{
	(void) game;
	(void) i;
	(void) j;
	int pos_x;
	int pos_y;
	// int player_pos= 0;

	// while (s[i])
	// {
	// 	if (check_is_single_map(s[i]))
	// 	{
	// 		puts("YES\n");
	// 	}
	// 	i++;
	// }
	// i = 0;
	// player_pos = pos_player(s);
	pos_player(s, &pos_x, &pos_y);
		// printf("%d\n", player_pos);
	// while (s[i])
	// {
		if (pos_x && pos_y)
		{
			back_track(game, s, pos_x, pos_y);
		}
	// 	i++;
	// }
	return (s);
}

void	parse(int ac, char *file, t_cube *game)
{
	if (ac <= 1 || ac >= 3)
		error_message(game, 0x1);
	// if (check_extension(file) == 0)
	// 	error_message(game, 0x2);
	game->map_2d = read_map_from_file(file, 0x0, 0x0);
	if (!game->map_2d)
		error_message(game, 0x3);
	init_counter(game);
	heigth_width(game);
	check_texture_intra(game, 0x0);
	check_valid_members(game, 0x0, 0x0);
	player_vision(game->map_2d, game);
	parse_entry(game, 0x0);
	// ft_load_textures(game);
	game->map = final_map(game, game->map_2d);
	game->final_map = get_final_map(game, game->map, 0 , 0);
	// 
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
