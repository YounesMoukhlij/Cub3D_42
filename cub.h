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
# define BOX_SIZE 40
# define BOX_SIZE_MINI_MAP 10
# define player_size 3
# define PI 3.14159265358979323846
# define rotation_speed 3 * (PI / 180)
# define wall_with 1
# define WINDOW_WIDTH 1500
# define WINDOW_HEITH 1000
# define player_size_mini_map 6
# define BOX_SIZE_MINI_MAP 10




typedef struct s_ray_tools
{
	float intercept_y;
	float intercept_x;
	float step_x;
	float step_y;
	float wall_y;
	float next_vertical_x;
	float next_vertical_y;
	float wall_vertical_x;
	float wall_horizontal_x;
	float wall_horizontal_y;
	float wall_vertical_y;
	int found_vertical_wall;
	float wall_x;
	float next_horizontal_x;
	float next_horizontal_y;
	float	horizontal_wall_distance;
	float	vertical_wall_distance;
	int	found_horizontal_wall;

} t_ray_tools;



typedef struct s_delete
{
	void				*ptr;
	struct s_delete		*next;
}						t_delete;

typedef struct s_colors
{
	int	r_c;
	int	g_c;
	int	b_c;
	int	r_f;
	int	g_f;
	int	b_f;
}	t_colors;


typedef struct s_counter
{
	int	a1;
	int	a2;
	int	a3;
	int	a4;
	int	a5;
	int	a6;
}	t_counter;


typedef struct s_text
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*c;
	char	*f;
}	t_text;

typedef struct s_ray_info
{
	float wall_x;
	float wall_y;
	float distance;
	int coloum;
	int index;
	struct s_ray_info *next;
} t_ray;

// typedef struct s_cube
// {	
// 	int 	player_x;
// 	int  	player_y;
// 	int  	player_y_mini_map;
// 	int  	player_x_mini_map;
// 	float    distance;
// 	int     was_vertical;
// 	float	fov_angle;////////
// 	float  	roation_angle;/////
// 	float	num_ray;///////////
// 	float 	is_facingDown;
// 	float 	is_facingLeft;
// 	int 	hit_v;
// 	float 	is_facingup;
// 	float 	is_facingRight;
// 	float  	move;
// 	int 	player_walk;
// 	int 	player_turn;
// 	int     map_widht;
// 	int     map_height;
// 	mlx_t 	*mlx;
// 	mlx_image_t *img;
// 	mlx_image_t *img_mini_map;
// 	char	*map_1d;
// 	char	**map_2d;
// 	char	**map;
// 	float ray_angle;
// 	t_text	*texture_walls;
// }	t_cube;

typedef struct s_png
{
	mlx_texture_t	*so;
	mlx_texture_t	*no;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*ciel;
	mlx_texture_t	*floor;
}	t_png;



typedef struct s_draws
{
	int dis;
	int j;
	int wall_heigth;
	int top;
	int bottom;
	int i;
	int r;
	int g;
	int b;
	int a;

} t_draws;








typedef struct s_cube
{
	int index;
	t_draws draws;
	char	**final_map;
	int		mini_heigth;
	int		mini_width;
	int 	player_x;
	float	rotation_angle;
	int  	player_y;
	int  	player_y_mini_map;
	int  	player_x_mini_map;

	float	num_ray;
	double	fov_angle;
	int     was_vertical;
	float 	player_new_y;
	float 	player_new_x;
	float 	is_facingDown;
	float 	is_facingLeft;
	int 	hit_v;
	t_png		*png;
	float 	is_facingup;
	float 	is_facingRight;
	float  move;
	int 	player_walk;
	int 	player_turn;
	int     map_widht;
	int     map_height;
	mlx_t 	*mlx;
	mlx_texture_t	*texture;
	mlx_image_t *img;
	mlx_image_t *img_wall;
	mlx_image_t *img_mini_map;
	char	*map_1d;
	char	**map_2d;
	char	**map;
	int	offset_x;
	int	offset_y;
		uint32_t		*color;
		int		real_map_width;
	int		real_map_heigth;
	float ray_angle;
	// double	rotation_angle;
	t_counter cnt;
	t_colors colors;
	t_ray_tools r_tools;
	t_text	texture_walls;
}	t_cube;


int ft_check_door(t_cube *game , int next_horizontal_x , int next_horizontal_y );
void ft_put_player(t_cube *game);
void ft_drawing_map(t_cube *game);
void	get_x(t_cube *game, t_ray *ray);
int 	ft_color(int  r, int  g, int  b, int  a);
float	ft_max(float a, float b);
float	ft_min(float a, float b);

void ft_drawing_map_element(t_cube *game);
void ft_draw_wall( t_cube *game, t_ray *ray);
void ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2);

void draw_line_DDA(t_cube *game);

    void init_tools(t_ray_tools rays_tools);

void       fifth_chapter(t_cube *game);
void        sixth_extra_chapter(t_cube *game, t_ray *ray);

void       sixth_chapter(t_cube *game, t_ray *ray);

// ******** PARSING ********

char	*get_next_line(int fd);
void	error_reading_map(int mode);
// char	**read_map_from_file(char *map_1d);
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
// void 	ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2);
int 	ft_check_walls(t_cube *game , int x , int y);
// void lst_add_back(t_ray **head);
// t_ray *lst_last(t_ray *head);


// ********** RAY_CAST ********

void ray_cast(int  colum , t_cube *game);
float ft_normalize(float angel);
void ft_test(t_cube *game);
int ft_check_door(t_cube *game , int next_horizontal_x , int next_horizontal_y );
void draw_line_DDA(t_cube *game);
int ft_check_walls(t_cube *game , int x , int y);
void ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2);
void ft_draw_wall( t_cube *game , t_ray *ray);


// ******** PARSING ********

char	*get_next_line(int fd);
void	error_reading_map(int mode);
char	**read_map_from_file(char *map_1d, int fd, int is_map);
// char	**read_map_from_file(char *map_1d);


void	error_message(t_cube *var, int mode);
void	parse(int ac, char *file, t_cube *var);

// ********** GARBAGE COLLECTOR ********

t_delete	*last_cmd_garbage(t_delete *lst);
void	add_back_garbage(t_delete **head, t_delete *node);
void	free_list(t_delete **head);
t_delete	*lstnew_garbage(void *str);
void	*ft_malloc(size_t size, int mode);
void	lstaddfront_garbage(t_delete **head, t_delete *node);


// ********** UTILS ********

int ft_calcule_distance(float x1, float y1, float x2 , float y2);
void	ft_free(char **s);
int		ft_strlen(char *s);
char	*ft_strdup(char *s1);
int		ft_atoi(char *str);
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
// void 	ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2 , int flag);
void 	ft_draw_line( t_cube *game,int x1, int y1, int x2, int y2);
int 	ft_check_walls(t_cube *game , int x , int y);
void lst_add_back(t_ray **head);
t_ray *lst_last(t_ray *head);



#endif
