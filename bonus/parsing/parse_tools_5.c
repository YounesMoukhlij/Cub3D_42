/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 14:14:53 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 17:20:06 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// int	case_1(char **s, int i, int j)
// {
// 	if (s[i + 1][j] == 32)
// 		return (1);
// 	if (s[i - 1][j] == 32)
// 		return (1);
// 	if (s[i][j + 1] == 32)
// 		return (1);
// 	if (s[i][j - 1] == 32)
// 		return (1);
// 	return (0x0);
// }

// int	case_2(char **s, int i, int j)
// {
// 	if (s[i + 1][j]  == 32)
// 		return (1);
// 	if (s[i - 1][j] == 32)
// 		return (1);
// 	if (s[i][j + 1] == 32)
// 		return (1);
// 	if (s[i][j - 1] == 32)
// 		return (1);
// 	return (0);
// }

// int	case_3(char **s, int i, int j)
// {
// 	if (s[i + 1][j] == 32)
// 		return (1);
// 	if (s[i - 1][j] == 32)
// 		return (1);
// 	if (s[i][j + 1] == 32)
// 		return (1);
// 	if (s[i][j - 1] == 32)
// 		return (1);
// 	return (0);
// }

// int	case_4(char **s, int i, int j)
// {
// 	if (s[i + 1][j] == 32)
// 		return (1);
// 	if (s[i - 1][j] == 32)
// 		return (1);
// 	if (s[i][j + 1] == 32)
// 		return (1);
// 	if (s[i][j - 1] == 32)
// 		return (1);
// 	return (0);
// }

int	case_1(char **s, int i, int j)
{
	if (s[i + 1][j] != '1' && s[i + 1][j] != '0'
		&& s[i + 1][j] != 'D' && s[i + 1][j] != 'N')
		return (1);
	if (s[i - 1][j] != '1' && s[i - 1][j] != '0'
		&& s[i - 1][j] != 'D' && s[i - 1][j] != 'N')
		return (1);
	if (s[i][j + 1] != '1' && s[i][j + 1] != '0'
		&& s[i][j + 1] != 'D' && s[i][j + 1] != 'N')
		return (1);
	if (s[i][j - 1] != '1' && s[i][j - 1] != '0'
		&& s[i][j - 1] != 'D' && s[i][j - 1] != 'N')
		return (1);
	return (0x0);
}

int	case_2(char **s, int i, int j)
{
	if (s[i + 1][j] != '1' && s[i + 1][j] != '0'
		&& s[i + 1][j] != 'D' && s[i + 1][j] != 'S')
		return (1);
	if (s[i - 1][j] != '1' && s[i - 1][j] != '0'
		&& s[i - 1][j] != 'D' && s[i - 1][j] != 'S')
		return (1);
	if (s[i][j + 1] != '1' && s[i][j + 1] != '0'
		&& s[i][j + 1] != 'D' && s[i][j + 1] != 'S')
		return (1);
	if (s[i][j - 1] != '1' && s[i][j - 1] != '0'
		&& s[i][j - 1] != 'D' && s[i][j - 1] != 'S')
		return (1);
	return (0);
}

int	case_3(char **s, int i, int j)
{
	if (s[i + 1][j] != '1' && s[i + 1][j] != '0'
		&& s[i + 1][j] != 'D' && s[i + 1][j] != 'W')
		return (1);
	if (s[i - 1][j] != '1' && s[i - 1][j] != '0'
		&& s[i - 1][j] != 'D' && s[i - 1][j] != 'W')
		return (1);
	if (s[i][j + 1] != '1' && s[i][j + 1] != '0'
		&& s[i][j + 1] != 'D' && s[i][j + 1] != 'W')
		return (1);
	if (s[i][j - 1] != '1' && s[i][j - 1] != '0'
		&& s[i][j - 1] != 'D' && s[i][j - 1] != 'W')
		return (1);
	return (0);
}

int	case_4(char **s, int i, int j)
{
	if (s[i + 1][j] != '1' && s[i + 1][j] != '0'
		&& s[i + 1][j] != 'D' && s[i + 1][j] != 'E')
		return (1);
	if (s[i - 1][j] != '1' && s[i - 1][j] != '0'
		&& s[i - 1][j] != 'D' && s[i - 1][j] != 'E')
		return (1);
	if (s[i][j + 1] != '1' && s[i][j + 1] != '0'
		&& s[i][j + 1] != 'D' && s[i][j + 1] != 'E')
		return (1);
	if (s[i][j - 1] != '1' && s[i][j - 1] != '0'
		&& s[i][j - 1] != 'D' && s[i][j - 1] != 'E')
		return (1);
	return (0);
}

int peter_csezsh(char **s, int i, int j)
{
	if (s[i][j] == '0' || s[i][j] == 'W'
		|| s[i][j] == 'E' || s[i][j] == 'N'
		|| s[i][j] == 'S' || s[i][j] == 'D')
		return (0x1);
	return (0x0);
}
