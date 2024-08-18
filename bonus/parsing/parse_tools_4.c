/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 14:34:39 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/18 12:14:32 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

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

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

char	*fill_spaces(char *s, int big_len, char *str)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = ft_strlen(s);
	str = ft_malloc(big_len + 2, 1);
	if (!s)
		return (NULL);
	ft_strcpy(str, s);
	while (tmp < big_len + 1)
	{
		str[tmp] = ' ';
		tmp++;
	}
	str[tmp] = '\0';
	return (str);
}

char	**ft_maping(t_cube *game, char **s, int i)
{
	while (s[i])
	{
		s[i] = fill_spaces(s[i], game->real_map_width, 0x0);
		printf("[%s]\n", s[i]);
		i++;
	}
	return (s);
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
	return (ft_maping(game, s, 0));
}

mlx_image_t	*open_image(char *path, t_cube *game)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		exit(1);
	img = mlx_texture_to_image(game->mlx, texture);
	if (!img)
	{
		mlx_delete_texture(texture);
		exit (0);
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
	game->png.arm = open_image("./assets/arm.png", game);
	game->png.door = open_image("./assets/door.png", game);
	if (!game->png.ea || !game->png.no || !game->png.so
		|| !game->png.we || !game->png.arm ||!game->png.door)
		error_message(game, 0x6);
}
