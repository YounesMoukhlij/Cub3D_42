/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:27:24 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/01 17:16:14 by youmoukh         ###   ########.fr       */
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

int	check_walls(char *s, int i, int length)
{
	int	j;

	j = 0x0;
	if (s[0x0] != '1' || s[ft_strlen(s) - 0x1] != '1')
		return (0x1);
	if (i == 0x6 || i == (length - 0x1))
	{
		while (s[j])
			if (s[j++] != '1')
				return (0x1);
	}
	return (0x0);
}

void	check_valid_members(t_cube *game, int i, int j)
{
	char	*str;

	while (game->map_2d[i])
	{
		j = 0;
		if (i > 5)
		{
			str = fix_the_map(game->map_2d[i], 0x0, 0x0, 0x0);
			// if (check_walls(str, i, get_length_heigth(game->map_2d, 0x0, 0x0)))
			// 		error_message(game, 0x4);
			while (str[j])
			{
				if (!(str[j] == '0' || str[j] == '1'
					|| str[j] == 'N' || str[j] == 'S'
					|| str[j] == 'W' || str[j] == 'E'))
					error_message(game, 0x4);
				j++;
			}
			free (str);
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
		free (str);
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

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		r;

	i = 0;
	sign = 1;
	r = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		r = r * 10;
		r += str[i] - '0';
		i++;
	}
	return (sign * r);
}

int	get_comma(char *s, int step)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
		{
			puts("COMMMMA FOUND\n");
			if (!step)
				break ;
			step--;
		}
		i++;
	}
	return (i);
}

void	parse_numbers(char *s)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split(s, ',');
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return ;
	}

}


void	parse_entry(t_cube *game, int i)
{
	char	*s1;
	char	*s2;
	int		len;

	len = 0;
	while (game->map_2d[i] && i < 6)
	{
		s1 = ft_substr(game->map_2d[i], 0x0,  2);
		if (!ft_strcmp(s1, "C ") || !ft_strcmp(s1, "F "))
		{
			s2 = ft_substr(game->map_2d[i], 0x2,  ft_strlen(game->map_2d[i]) - 1);
			printf("main str ->[%s]\n\n\n", s2);
			parse_numbers(s2);
		}
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
	check_texture_intra(game, 0x0);
	parse_entry(game, 0x0);
	// check_valid_members(game, 0x0, 0x0);
	heigth_width(game);
	player_vision(game->map_2d, game);


	int i  = 0;
	puts("\n\n\n\033[32m --->< THE MAP ><---\033[0m\n\n");
	while (game->map_2d[i])
		printf("%s\n", game->map_2d[i++]);
	puts("\n");
	printf("the heigth ---=[%d]\n", game->real_map_heigth);
	printf("the width ---=[%d]\n", game->real_map_width);
	puts("good\n");
}

