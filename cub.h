/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:49 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/01 17:14:43 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

# include "MLX42/include/MLX42/MLX42.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <math.h>

# define BUFFER_SIZE 1
# define player_speed 10
# define box_size 90
# define player_size 3
# define PI 3.14159265358979323846
# define reation_speed 3 * (PI / 180)
# define wall_with 1


typedef struct s_text
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*fF;
}	t_text;

typedef struct s_ray_info
{
	float wall_x;
	float wall_y;
	float distance;
	int coloum;
	struct s_ray_info *next;
} t_ray;

typedef struct s_cube
{	
	int 	player_x;
	int  	player_y;
	float     *rays;
	float    distance;
	int     was_vertical;
	float 	player_new_y;
	float 	player_new_x;
	float 	is_facingDown;
	float 	is_facingLeft;
	int 	hit_v;
	float 	is_facingup;
	float 	is_facingRight;
	float  move;
	int 	player_walk;
	int 	player_turn;
	int     map_widht;
	int     map_height;
	mlx_t 	*mlx;
	mlx_image_t *img;
	char	*map_1d;
	char	**map_2d;
	char	**map;
	float ray_angle;
	t_text	*texture_walls;
}	t_cube;

// ******** PARSING ********

char	*get_next_line(int fd);
void	error_reading_map(int mode);
char	**read_map_from_file(char *map_1d);
void	error_message(t_cube *var, int mode);
void	parse(int ac, char *file, t_cube *var);

// ********** UTILS ********

void	ft_free(char **s);
int		ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	**ft_split(char *s, char c);
int		ft_strcmp(char *s1, char *s2);
void	*ft_calloc(int num, int size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char *s1, char *set);
char	*ft_substr(char *s, int start, int len);
void 	ft_get_player_position(t_cube *game);
void 	ft_drawing_map_element(t_cube *game);
void 	ft_draw_square(t_cube *game, int x , int y);
void 	ft_drawing_map(t_cube *game);
void 	set_values(t_cube *game);
void 	ft_put_player(t_cube *game);
void 	ft_draw_floor(t_cube *game, int x , int y);
void 	ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2 , int flag);
int 	ft_check_walls(t_cube *game , int x , int y);
void lst_add_back(t_ray **head);
t_ray *lst_last(t_ray *head);


#endif
