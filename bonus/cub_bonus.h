/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:17:49 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 19:52:49 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# include "MLX42/MLX42.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUFFER_SIZE 1
# define BOX_SIZE 200
# define BOX_MINI 10
# define PLAYER_SIZE 3
# define PI 3.14159265358979323846
# define WALL_WIDTH 1
# define WINDOW_WIDTH 1500
# define WINDOW_HEITH 1000
# define PLAYER_SIZE_MINI_MAP 6
# define BOX_MINI 10

typedef struct s_ray_tools
{
	float			intercept_y;
	float			intercept_x;
	float			step_x;
	float			step_y;
	float			wall_y;
	float			next_vertical_x;
	float			next_vertical_y;
	float			wall_vertical_x;
	float			wall_horizontal_x;
	float			wall_horizontal_y;
	float			wall_vertical_y;
	int				found_vertical_wall;
	float			wall_x;
	float			next_horizontal_x;
	float			next_horizontal_y;
	float			horizontal_wall_distance;
	float			vertical_wall_distance;
	int				found_horizontal_wall;

}					t_ray_tools;

typedef struct s_tools
{
	int				i;
	int				f;
	int				j;
	char			*tmp;
}					t_tools;

typedef struct s_delete
{
	void			*ptr;
	struct s_delete	*next;
}					t_delete;

typedef struct s_pparse
{
	int				n;
	int				e;
	int				s;
	int				w;
}					t_pparse;

typedef struct s_extra
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_extra;

typedef struct s_colors
{
	int				r_c;
	int				g_c;
	int				b_c;
	int				r_f;
	int				g_f;
	int				b_f;
}					t_colors;

typedef struct s_counter
{
	int				a1;
	int				a2;
	int				a3;
	int				a4;
	int				a5;
	int				a6;
}					t_counter;

typedef struct s_text
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*c;
	char			*f;
}					t_text;

typedef struct s_ray
{
	float			wall_x;
	float			wall_y;
	float			distance;
	int				coloum;
	int				index;
}					t_ray;

typedef struct s_png
{
	mlx_image_t		*so;
	mlx_image_t		*no;
	mlx_image_t		*we;
	mlx_image_t		*ea;
	mlx_image_t		*arm;
	mlx_image_t		*_1;
	mlx_image_t		*_2;
	mlx_image_t		*_3;
	mlx_image_t		*_4;
	mlx_image_t		*_5;
	mlx_image_t		*door;

}					t_png;

typedef struct s_draws
{
	int				dis;
	int				j;
	int				butt;
	int				topp;
	int				incr;
	int				wall_heigth;
	int				top;
	int				bottom;
	int				i;
	int				r;
	int				g;
	int				b;
	int				a;

}					t_draws;

typedef struct s_cube
{
	float			mouse_speed;
	float			rotation_speed;
	int				start_x;
	int				start_y;
	int				index;
	int				player_speed;
	int				mouse_stat;
	t_tools			twilzat;
	t_draws			draws;
	char			**final_map;
	int				mini_heigth;
	int				mini_width;
	int				player_x;
	float			rotation_angle;
	int				player_y;
	int				player_y_mini_map;
	int				player_x_mini_map;
	int				player_vision;
	int				raduis;
	t_extra			extra;
	t_pparse		parse_p;
	float			num_ray;
	double			field_of_view_angle;
	int				was_vertical;
	float			player_new_y;
	float			player_new_x;
	float			is_facingdown;
	float			is_facingleft;
	int				hit_v;
	t_png			png;
	float			is_facingup;
	float			is_facingright;
	float			move;
	int				player_walk;
	int				player_turn;
	int				map_widht;
	int				map_height;
	mlx_t			*mlx;

	mlx_texture_t	*texture;

	mlx_image_t		*img_wall;

	mlx_image_t		*img_mini_map;
	mlx_image_t		*img;
	char			*map_1d;
	char			**map_2d;
	char			**map;
	int				offset_x;
	int				offset_y;
	uint32_t		*color;
	int				real_map_width;
	int				real_map_heigth;
	float			ray_angle;
	t_counter		cnt;
	t_colors		colors;
	t_ray_tools		r_tools;
	t_text			texture_walls;
}					t_cube;

void				ft_handle_image(t_cube *game, t_ray *ray, int x);
void				ft_handle_mouse(void *param);
int					case_1(char **s, int i, int j);
int					case_2(char **s, int i, int j);
int					case_3(char **s, int i, int j);
int					case_4(char **s, int i, int j);
int					peter_csezsh(char **s, int i, int j);
int					ultra_check(t_cube *game, int mode);
void				extra_one(t_cube *game, double *x, double *y);
void				extra_two(t_cube *game, double *x, double *y);
void				extra_tree(t_cube *game, double *x, double *y);
void				extra_four(t_cube *game, double *x, double *y);
void				ft_check_move(void *tmp);
void				init_image(t_cube *game);
void				draw_wall_one(t_cube *game, t_ray *ray);
void				draw_line_dda(t_cube *game);
int					check_me(int x, int y, int width, int heigth);

int					ft_check_sprit(t_cube *game, int next_horizontal_x,
						int next_horizontal_y);
void				get_path(t_cube *game, int i, char *str);

void				fill_colors(t_cube *game, char *s, int mode);

void				player_vision(char **s, t_cube *game);

int					parse_numbers(char *s);

void				check_valid_members(t_cube *game, int i, int j);

int					check_walls(char *s, int i, int stat, t_cube *game);

void				parse_entry(t_cube *game, int i);

int					check_one(t_cube *game, char *s);

int					ultra_check(t_cube *game, int mode);

char				*fill_chars(t_cube *game, char *s);

void				check_texture_intra(t_cube *game, int i);
void				init_counter(t_cube *game);
int					player_num(t_cube *game);

void				check_valid_members(t_cube *game, int i, int j);
void				player_vision(char **s, t_cube *game);
void				heigth_width(t_cube *game);
int					ft_strlen_ii(char *s);

int					parse_numbers(char *s);
int					check_colesion(t_cube *game, int x, int y);
void				fill_colors(t_cube *game, char *s, int mode);

void				get_path(t_cube *game, int i, char *str);

int					check_extension(char *file, int mode);
int					ft_check_door(t_cube *game, int next_horizontal_x,
						int next_horizontal_y);
void				ft_put_player(t_cube *game);
void				ft_drawing_map(t_cube *game);
void				get_x(t_cube *game, t_ray *ray);
int					ft_color(int r, int g, int b, int a);
float				ft_max(float a, float b);
float				ft_min(float a, float b);
void				draw_line_dda(t_cube *game);

void				init_tools(t_ray_tools rays_tools);

void				fifth_chapter(t_cube *game, t_ray *ray);
void				sixth_extra_chapter(t_cube *game, t_ray *ray);
int					check_color(t_cube *game, char **str);

void				sixth_chapter(t_cube *game, t_ray *ray);
void				parse_s(t_cube *game, char *s, int i);
int					get_length_heigth(char **str, int mode, int i);
char				*get_next_line(int fd);
void				error_reading_map(int mode);
void				error_message(t_cube *var, int mode);
void				parse(int ac, char *file, t_cube *var);

int					check_view(t_cube *game, t_ray *ray);

char				*fix_the_map(char *s, int i, int flag, int j);

// ********** RAY_CAST ********

int					check_walls(char *s, int i, int stat, t_cube *game);

void				ray_cast(int colum, t_cube *game);
float				ft_normalize(float angel);
void				ft_test(t_cube *game);
int					ft_check_door(t_cube *game, int next_horizontal_x,
						int next_horizontal_y);
void				draw_line_dda(t_cube *game);
int					ft_check_walls(t_cube *game, int x, int y);
void				ft_draw_wall(t_cube *game, t_ray *ray, int z, int x);

char				*get_next_line(int fd);
void				error_reading_map(int mode);
char				**read_map_from_file(char *map_1d, int fd, int is_map);

void				error_message(t_cube *var, int mode);
void				parse(int ac, char *file, t_cube *var);

t_delete			*last_cmd_garbage(t_delete *lst);
void				add_back_garbage(t_delete **head, t_delete *node);
void				free_list(t_delete **head);
t_delete			*lstnew_garbage(void *str);
void				*ft_malloc(size_t size, int mode);
void				lstaddfront_garbage(t_delete **head, t_delete *node);

int					ft_calcule_distance(float x1, float y1, float x2, float y2);
void				ft_free(char **s);
int					ft_strlen(char *s);
char				*ft_strdup(char *s1);
int					ft_atoi(char *str);
char				**ft_split(char *s, char c);
int					ft_strcmp(char *s1, char *s2);
void				*ft_calloc(int num, int size);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);

char				*ft_substr(char *s, int start, int len);
void				ft_get_player_position(t_cube *game);
void				ft_drawing_map_element(t_cube *game, int i, int j);
void				ft_draw_square(t_cube *game, int x, int y);
void				ft_drawing_map(t_cube *game);
void				set_values(t_cube *game);
void				ft_put_player(t_cube *game);
void				ft_draw_floor(t_cube *game, int x, int y);
int					ft_check_walls(t_cube *game, int x, int y);
mlx_image_t			*open_image(char *path, t_cube *game);

int					parse_numbers(char *s);

void				ft_load_textures(t_cube *game);
mlx_image_t			*open_image(char *path, t_cube *game);
char				**final_map(t_cube *game, char **str);

int					get_length_heigth(char **str, int mode, int i);
char				*fix_the_map(char *s, int i, int flag, int j);

void				check_valid_members(t_cube *game, int i, int j);
void				player_vision(char **s, t_cube *game);

#endif
