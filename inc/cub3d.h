/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flmuller <flmuller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:08:13 by flmuller          #+#    #+#             */
/*   Updated: 2025/01/13 13:30:54 by flmuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* Library */

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

# define TILE 8
# define SC_WIDTH 1200
# define SC_HEIGHT 600
# define SPEED 0.1
# define ROT_SPEED 0.03
# define GAME_NAME "Cub3d"
# define FOV 66
# define BUFFER_DIST 0.08
# define BPP 32
/* Structure */

typedef struct s_texture
{
	void			*img;
	unsigned int	*addr;
	int				bits_per_pixels;
	int				line_length;
	int				endian;
	int				height;
	int				width;
	char			*path;
}	t_texture;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_dpos
{
	double	x;
	double	y;
}	t_dpos;

typedef struct s_player
{
	t_pos	ppos;
	float	angle;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_arrow
{
	t_coord	head;
	t_coord	left;
	t_coord	right;
}	t_arrow;

typedef struct s_map_data
{
	char			**map;
	int				width;
	int				height;
	t_player		player;
	double			player_pos_x;
	double			player_pos_y;
	int				check_pos_x;
	int				check_pos_y;
	int				map_error;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
}	t_map_data;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_verl_inf
{
	int				drawstart;
	int				drawend;
	int				texturex;
	int				x;
	int				textwidth;
	int				textheight;
	double			step;
	double			texture_pos;
	int				texture_y;
	unsigned int	pixel;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_verl_inf;

typedef struct s_data
{
	int				flag_color_c;
	int				flag_color_f;
	int				screen_width;
	int				screen_height;
	void			*mlx;
	void			*mlx_win;
	t_img			*img;
	t_texture		texture[4];
	t_dpos			raydir;
	unsigned int	**wall;
	char			keys[256];
	t_color			*colors_floor;
	t_color			*colors_ceiling;
	int				mouse_x;
	t_map_data		map_data;
	int				line_height;
	t_verl_inf		*verl_inf;
}	t_data;

/* Fonctions */
int		key_release(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
int		parsing(int ac, char **av, t_data *data);
int		too_many_player(t_map_data map_data);
int		iswall(t_map_data *map_data, int x, int y);
void	init_var(t_data *data);

/* input.c */
void	action_key(t_data *data);
int		handle_keypress(int keycode, t_data *data);
int		handle_mouse_move(int x, int y, t_data *data);
int		close_and_clean(t_data *data);

/* camera.c */
void	turn_left(t_map_data *map_data);
void	turn_right(t_map_data *map_data);

/* movement.c */
void	strafe_left(t_map_data *map_data);
void	strafe_right(t_map_data *map_data);
void	forward(t_map_data *map_data);
void	backward(t_map_data *map_data);
int		valid_pos(t_map_data *map_data, float x, float y);

/* minimap/map_pos.c */
t_pos	create_pos(float x, float y);
t_coord	create_coord(int x, int y);

/* img_gen/img.c*/
void	put_pixel(t_img *img, int x, int y, int color);
void	init_img(t_data *data);

/* utils.c */
void	free_map_data(t_map_data *map_data);
void	free_array(char **array);
void	coordswap(t_coord *a, t_coord *b);
void	clean_all(t_data *data);
void	free_wall(unsigned int **wall);
//void	free_texture(t_texture *texture);
void	free_all_textures(t_data *data);
void	free_single_texture(t_texture *texture, t_data *data);
//void	free_single_texture(t_texture *texture);
void	free_img(t_data *data);
void	free_color(t_data *data);
void	free_color_and_data(t_data *data, char *treated_line);

/* minimap/create_mmap.c */
int		loop_routine(t_data *data);
void	parse_mmap(t_data *data);
void	draw_tile(t_data *data, char c, t_coord *pen);
int		select_color(char c);
int		is_onmap(char c);

/* minimap/player.c */
void	set_player(t_data *data);
void	set_arrow_point(t_player *player, t_arrow *arrow);
int		is_player_mmap(char c);

/* mlxinit.c */
void	init_map(t_data *data);
void	init_win(t_data *data);
void	calc_plane(t_player *player);

/* raycast/draw.c */
int		interpolate_x(t_coord p1, t_coord p2, int y);
void	fill_triangle(t_data *data, t_arrow *player);
void	draw_line(t_data *data, t_coord a, t_coord b);
void	calc_line(t_coord *d, t_coord *s, t_coord *a, int *err);
void	fill_part(t_coord *start, t_coord *end, t_arrow *player, int y);
void	init_verline(t_data *data, int textureindex);

/*init.c*/
int		if_temp_null(t_map_data *map_data, char **temp);
char	**manage_temp(t_map_data *map_data, char *line);
int		save_line_in_map(t_map_data *map_data, char *line);
int		create_map(t_map_data *map_data, char *map_file);
int		treat_line(char *treated_line, t_map_data *map_data);
int		create_map_for_game(t_map_data *map_data, char *map_file);
int		define_player_pos(t_map_data *map_data);
int		define_check_pos(t_map_data *map_data);
void	allocate_colors(t_data *data);
void	allocate_verline_data(t_data *data);

/*src/parsing.c*/
int		check_extension_file_name(char *name, int case_num);
int		does_file_exist(char *name);
void	display_map_data(t_map_data *map_data);
int		check_walls_horizontal(t_map_data *map_data);
int		check_walls_vertical(t_map_data *map_data);
int		check_allowed_caracters(t_map_data *map_data);

/*src/floodfill.c*/
void	flood_map(t_map_data *map_data, int x, int y);
int		check_flood_fill(t_map_data *map_data);
int		map_free_after_flood_fill(t_map_data *map_data);
int		routine_floodfill(t_map_data *map_data, char *map_file);
int		routine_parsing(t_map_data *map_data, int ac, char **av);

/* routine.c */
int		loop_routine(t_data *data);

/* raycasting */
void	draw_ceiling(t_data *data);
void	draw_floor(t_data *data);
void	verline(t_data *data, int textureindex);
void	cast_rays_and_render(t_data *data);
void	rotate(t_player *data, double rotSpeed, int direction);

/* retreive_colors.c*/

void	retreive_colors(char *treated_line, t_data *data);
int		retrieve_colors_floor(char *treated_line, t_data *data);
void	treat_col_val_floor(t_data *data, int *i, char *treated_line, int z);
int		retrieve_colors_ceiling(char *treated_line, t_data *data);
void	treat_col_val_ceiling(t_data *data, int *i, char *treated_line, int z);
void	manage_single_color(char *treated_line,
			int *i, int *y, char *alpha_num);
void	assign_r_g_b_floor(t_data *data, int z, int color_value);
void	assign_r_g_b_ceiling(t_data *data, int z, int color_value);
void	check_f_c_exist(char *treated_line, t_data *data);

/* init texture */
void	init_images_walls(t_data *data);
void	allocate_wall(t_data *data, int i);
void	print_all_pixels(t_data *data, int i);
void	init_texture(t_data *data);

/* init2.c*/
int		retreive_infos_textures(t_data *data, char **av);
int		is_texture_path(char *treated_line);
int		retreive_textures(t_data *data, char *treated_line);
int		check_texture_file_exists(t_data *data);

void	calc_deltadist(t_data *data, t_dpos *deltadist);
void	calc_sidedist(t_data *data, t_dpos *sidedist,
			t_coord *map, t_dpos deltadist);
void	init_step(t_data *data, t_coord *step);
void	init_perp_wall_d(int side, double *perp_wall_d,
			t_dpos sidedist, t_dpos deltadist);
void	calc_dist(t_data *data, t_coord *map, int *side, double *perp_wall_d);
void	draw_define(double perp_wall_d, t_data *data);
void	calc_wallx(double *wallx, t_data *data, int side, double perp_wall_d);
int		get_textureindex(t_data *data, int side);
int		raycast(t_data *data);
void	init_raydir(t_data *data);
int		get_texturex(t_data *data, double wallx, int side);

#endif