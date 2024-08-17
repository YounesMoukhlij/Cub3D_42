/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:48:22 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 20:07:17 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	error_msg(int mode)
{
	if (mode == 11)
		write(STDERR_FILENO, "Map's is Missed\n", 17);
	else if (mode == 10)
		write(STDERR_FILENO, "Color's Problem.\n", 17);
	else if (mode == 300)
		write(STDERR_FILENO, "Door's Problem.\n", 17);
}

void	error_message(t_cube *var, int mode)
{
	(void) var;
	write(STDERR_FILENO, "Error\n", 0x6);
	if (mode == 0x1)
		write(STDERR_FILENO, "Parameters Not Valid\n", 22);
	else if (mode == 0x2)
		write(STDERR_FILENO, "Extension Not Valid\n", 21);
	else if (mode == 0x3)
		write(STDERR_FILENO, "Map Not Loaded\n", 16);
	else if (mode == 0x4)
		write(STDERR_FILENO, "Map's Members are not Valid\n", 29);
	else if (mode == 5)
		write(STDERR_FILENO, "malloc failed\n", 12);
	else if (mode == 6)
		write(STDERR_FILENO, "Textures cant be Loaded\n", 12);
	else if (mode == 7)
		write(STDERR_FILENO, "Problem Concerning Doors\n", 26);
	else if (mode == 8)
		write(STDERR_FILENO, "Walls Aren't Correctly build.\n", 31);
	else if (mode == 9)
		write(STDERR_FILENO, "Player's Problem.\n", 35);
	else
		error_msg(mode);
	exit(0x1);
}

void	error_reading_map(int mode)
{
	write(STDERR_FILENO, "Error\n", 0x6);
	if (mode == 0x1)
		write(STDERR_FILENO, "Map doe not Exist\n", 19);
	else if (mode == 0x2)
		write(STDERR_FILENO, "Map Not Valid\n", 15);
	else if (mode == 0x3)
		write(STDERR_FILENO, "Map Not Loaded\n", 16);
	exit(0x1);
}
