/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/21 17:00:08 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_extension(char *file)
{
	int	i;

	i = 0x0;
	while (file[i])
	{
		if (file[i] == '.' && file[i + 0x1] == 'c'
			&& file[i + 0x2] == 'u' && file[i + 0x3] == 'b' && file[i + 0x4] == '\0')
			return (0x1);
		i++;
	}
	return (0x0);
}

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

int	check_walls(char *s, int i, int stat, t_cube *game)
{
	if (stat == 6 || stat == game->real_map_heigth + 5)
	{
		while (s[i])
		{
			if (s[i++] != '1')
				return (1);
		}
	}
	if (s[0x0] != '1' || s[ft_strlen(s) - 0x1] != '1')
		return (0x1);
	// i = 0;
	// while (s[i])
	// {
	// 	while (s[i] && s[i] == ' ')
	// 	{
	// 		i++;
	// 		if (s[i] == ' ' && s[i + 1] != ' ' && s[i + 1])
	// 		{
	// 			puts("YOUNES");
	// 			return (0x1);
	// 		}
	// 	}
	// 	if (!s[i])
	// 		break ;
	// 	i++;
	// }
	printf("%s\n", s);
	return (0x0);
}

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	i= 6;
	while (game->map_2d[i] && i > 5)
	{
		j = 0;
		str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
		// printf("%s\n", ft_strtrim(game->map_2d[i], " "));
		if (check_walls(ft_strtrim(game->map_2d[i], " "), 0x0, i, game))
		{
			puts("ERROR CAPTed \n");
			error_message(game, 0x4);
		}
		while (str[j])
		{
			if (!(str[j] == '0' || str[j] == '1'
				|| str[j] == 'N' || str[j] == 'S'
				|| str[j] == 'W' || str[j] == 'E'))
				error_message(game, 0x4);
			j++;
		}
		i++;
	}
}

int	ultra_check(t_cube *game)
{
	if (game->cnt.a1 > 0x1
		|| game->cnt.a2 > 0x1
		|| game->cnt.a3 > 0x1
		|| game->cnt.a4 > 0x1
		|| game->cnt.a5 > 0x1
		|| game->cnt.a6 > 0x1)
		return (0x1);
	return (0);
}

void	check_texture_intra(t_cube *game, int i)
{
	char	*str;

	while (game->map_2d[i] && i < 0x6)
	{
		str = ft_substr(game->map_2d[i], 0x0,  2);
		if (!ft_strcmp(str, "NO"))
			game->cnt.a1++;
		else if (!ft_strcmp(str, "SO"))
			game->cnt.a2++;
		else if (!ft_strcmp(str, "EA"))
			game->cnt.a3++;
		else if (!ft_strcmp(str, "C "))
			game->cnt.a4++;
		else if (!ft_strcmp(str, "F "))
			game->cnt.a5++;
		else if (!ft_strcmp(str, "WE"))
			game->cnt.a6++;
		i++;
	}
	if (ultra_check(game))
		error_message(game, 0x4);
}

void	init_counter(t_cube *game)
{
	game->cnt.a1 = 0;
	game->cnt.a2 = 0;
	game->cnt.a3 = 0;
	game->cnt.a4 = 0;
	game->cnt.a5 = 0;
	game->cnt.a6 = 0;
}

int	ft_strlen_ii(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != 32 && s[i] != 9)
			len++;
		i++;
	}
	return (len);
}

void	heigth_width(t_cube *game)
{
	int	i;
	int	j;

	i = 6;
	j = 0;
	while (game->map_2d[i])
	{
		if (j <= ft_strlen_ii(game->map_2d[i]))
			j = ft_strlen_ii(game->map_2d[i]);
		i++;
	}
	game->real_map_width = j;
	game->real_map_heigth = get_length_heigth(game->map_2d, 0, 6);
}

// PLAYER VISION 
void	player_vision(char **s, t_cube *game)
{
	int	i;
	int	j;

	i = 6;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (s[i][j] == 'N')
				game->rotation_angle = (3 * PI) / 2;
			else if (s[i][j] == 'S')
				game->rotation_angle = PI / 2;
			else if (s[i][j] == 'W')
				game->rotation_angle = PI;
			else if (s[i][j] == 'E')
				game->rotation_angle = 0;
			j++;
		}
		i++;
	}
}

int	parse_numbers(char *s)
{
	char	**str;
	int		i;
	int		j;

	i = 0;
	str = ft_split(s, ',');
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!(str[i][j] >= '0' && str[i][j] <= '9'))
				return (1);
			j++;
		}
		if (ft_atoi(str[i]) > 255 || ft_atoi(str[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

void	fill_colors(t_cube *game, char *s, int mode)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split(s, ',');
	while (str[i])
	{
		if (!mode && !i)
			game->colors.r_c = ft_atoi(str[i]);
		else if (!mode && i == 1)
			game->colors.g_c = ft_atoi(str[i]);
		else if (!mode && i == 2)
			game->colors.b_c = ft_atoi(str[i]);
		else if (mode && !i)
			game->colors.r_f = ft_atoi(str[i]);
		else if (mode && i == 1)
			game->colors.g_f = ft_atoi(str[i]);
		else if (mode && i == 2)
			game->colors.b_f = ft_atoi(str[i]);
		i++;
	}
}

void	get_path(t_cube *game, int i, char *str)
{
	char	*s;

	s = ft_substr(game->map_2d[i], 3, ft_strlen(game->map_2d[i]) - 1);
	if (!s)
		return ;
	if (!ft_strcmp(str, "NO"))
		game->texture_walls.no = ft_strdup(s);
	else if (!ft_strcmp(str, "SO"))
		game->texture_walls.so = ft_strdup(s);
	else if (!ft_strcmp(str, "EA"))
		game->texture_walls.ea = ft_strdup(s);
	else if (!ft_strcmp(str, "WE"))
		game->texture_walls.we = ft_strdup(s);
}

void	parse_entry(t_cube *game, int i)
{
	char	*s1;
	char	*s2;

	while (game->map_2d[i] && i < 6)
	{
		s1 = ft_substr(ft_strtrim(game->map_2d[i], " "), 0x0,  2);
		if (!ft_strcmp(s1, "C ") || !ft_strcmp(s1, "F "))
		{
			s2 = ft_substr(ft_strtrim(game->map_2d[i], " "), 0x2,  ft_strlen(game->map_2d[i]) - 1);
			if (parse_numbers(s2))
				error_message(game, 0);
			if (!ft_strcmp(s1, "C "))
				fill_colors(game, s2, 0);
			else if (!ft_strcmp(s1, "F "))
				fill_colors(game, s2, 1);
		}
		if (!ft_strcmp(s1, "NO") || !ft_strcmp(s1, "SO")
			|| !ft_strcmp(s1, "EA") || !ft_strcmp(s1, "WE"))
			get_path(game, i, s1);
		i++;
	}
}

void	parse(int ac, char *file, t_cube *game)
{
	if (ac <= 1 || ac >= 3)
		error_message(game, 0x1);
	if (check_extension(file) == 0)
		error_message(game, 0x2);
	game->map_2d = read_map_from_file(file);
	if (!game->map_2d)
		error_message(game, 0x3);
	init_counter(game);
	heigth_width(game);
	check_texture_intra(game, 0x0);
	check_valid_members(game, 0x0, 0x0);
	parse_entry(game, 0x0);
	player_vision(game->map_2d, game);
	
	puts("\n\n\n\033[32m --->< THE PATHs ><---\033[0m\n\n");
	printf("NO  ---=---[%s]\n", game->texture_walls.no);
	printf("SO  ---=---[%s]\n", game->texture_walls.so);
	printf("EA  ---=---[%s]\n", game->texture_walls.ea);
	printf("WE  ---=---[%s]\n", game->texture_walls.we);
	
	puts("\n\n\n\033[32m --->< THE COLORS ><---\033[0m\n\n");
	printf("C r ---=---[%d]\n", game->colors.r_c);
	printf("C g ---=---[%d]\n", game->colors.g_c);
	printf("C b ---=---[%d]\n", game->colors.b_c);
	printf("F r ---=---[%d]\n", game->colors.r_f);
	printf("F g ---=---[%d]\n", game->colors.g_f);
	printf("F b ---=---[%d]\n", game->colors.b_f);

	// int i  = 0;
	// puts("\n\n\n\033[32m --->< THE MAP ><---\033[0m\n\n");
	// while (game->map_2d[i])
	// 	printf("%s\n", game->map_2d[i++]);
	puts("\n");
	printf("the heigth ---=[%d]\n", game->real_map_heigth);
	printf("the width ---=[%d]\n", game->real_map_width);
	puts("\n\n\n\n \033[41mCONGRATS ----> good \033[0m \n\n\n");
}

