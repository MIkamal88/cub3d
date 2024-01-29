/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 07:29:25 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/23 13:32:44 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/libft/includes/get_next_line.h"
# include "colors.h"
# include "keybinds.h"

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	800
# define SCENE_SIZE		1024000
# define TILE_SIZE 		64
# define FOV	1.0471975500000001 // 60 degrees in radians (field of view)
# define FORWARD 1
# define BACKWARD -1
# define LEFT 1
# define RIGHT -1
# define CLOCKWISE 1
# define ANTICLOCKWISE -1

# define ON_KEYDOWN	2
# define ON_KEYUP	3
# define ON_DESTROY	17

# define MINIMAP_WHITE 0xFFFFFF
# define MINIMAP_RED 0xFF0000
# define MINIMAP_BLACK 0x000000

# define TEXT_COLOR	0xFFFFFF

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_cardinal
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
}	t_cardinal;

typedef enum RGB
{
	R = 0,
	G,
	B,
	TOTAL,
}	t_rgb;

typedef enum type
{
	EMPTY = 0,
	WALL = 1,
	HALL = 2,
	PLAYER = 3,
}	t_type;

typedef struct s_point
{
	int		x;
	int		y;
	int		type;
	int		local_x_max;
	t_bool	visited;
}	t_point;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_length;
}	t_img;

typedef struct s_path
{
	char	*xpm_file;
	int		cardinal;
}	t_path;

typedef struct s_texture
{
	t_path	*path;
	t_img	*texture_img;
	t_bool	is_set;
}	t_texture;

typedef struct s_map
{
	int			rows;
	int			x_max;
	int			floor[TOTAL];
	t_bool		floor_set;
	int			ceiling[TOTAL];
	t_bool		ceiling_set;
	t_texture	**textures;
	t_point		**grid;
}	t_map;

enum e_errs
{
	EXIT,
	ARGS_ERR,
	MALLOC_ERR,
	MAP_ERR,
	IMG_ERR,
};

typedef struct s_win
{
	void	*mlx;
	void	*m_win;
	int		width;
	int		height;
}	t_win;

typedef struct s_coordinate
{
	float			x;
	float			y;
}	t_coordinate;

typedef struct s_movement
{
	int				walk_direction;
	int				side_direction;
	int				turn_direction;
}	t_movement;

typedef struct s_player
{
	t_point			*pos;
	t_point			*pos_scaled;
	t_coordinate	*pos_game;
	int				cardinal;
	t_bool			set;
	t_movement		movement;
	float			rotation_angle;
}	t_player;

typedef struct s_direction
{
	bool			is_up;
	bool			is_down;
	bool			is_right;
	bool			is_left;
}	t_direction;

typedef struct s_ray
{
	float		angle;
	float		distance;
	t_direction	direction;
	float		hit_x;
	float		hit_y;
	bool		is_up;
}	t_ray;

typedef struct s_data
{
	t_map		*map;
	t_img		*scene;
	t_win		*win;
	t_player	*player;
	int			is_running;
	t_ray		*rays;
	int			*game_color_buffer;

}	t_data;

typedef struct s_colision
{
	float			distance;
	bool			found_wall;
	float			check_x;
	float			check_y;
	bool			is_horizontal;
	t_coordinate	next_interception;
	t_coordinate	intcpt;
	t_coordinate	wall_hit;
	t_coordinate	step;

}	t_colision;

typedef struct s_wall
{
	float			projected_wall_dist;
	float			corrected_ray_distance;
	int				projected_wall_height;
	int				top_pixel;
	int				bottom_pixel;
	int				texel_color;
	int				x_texture_offset;
	int				y_texture_offset;
	int				distance_from_top;
	int				orientation;
}					t_wall;

// Mapping and Grid Functions
void		init_player(t_data *cub3d);
void		map_read(t_data *cub3d, char *filename);
void		init_textures(t_data *cub3d, int cardinal);
char		*validate_texture(t_data *cub3d, char *filename, char *direction);
t_bool		read_textures(t_data *cub3d, char *filename);
t_bool		load_texture(t_data *cube, int cardinal);
t_bool		read_load_texture(t_data *cub3d, char *filename);
t_bool		set_floor_ceiling(t_data *cub3d, char *filename);
t_bool		load_grid(t_data *cub3d, char *filename);
t_bool		check_assets(t_data *cub3d);
t_bool		is_closed(t_data *cub3d, int x, int y);

// Drawing
void		pixel_put(t_img *img, int x, int y, int color);
int			create_trgb(int r, int g, int b);
int			get_texture_color(t_img *texture, int x, int y);
int			pixel_get(t_img *img, int x, int y);

// Utils Functions
t_bool		map_start(char *line);
t_bool		valid_extension(char *file, char *ext);

// Raycasting
void		ray_casting(t_data *cub3d);
int			render_loop(t_data *cub3d);
void		render_walls(t_data *cub3d);
void		get_current_rotation_angle(t_data *cub3d);
int			key_push(int keycode, t_data *cube);
int			key_release(int keycode, t_data *cube);
bool		has_wall(t_data *data, float x, float y);
bool		map_limits(t_data *data, float x, float y);
float		wall_hit_distance(float x0, float y0, float x1, float y1);
void		analyze_colision(t_data *data, t_colision *col, bool dir);
void		draw_floor(t_data *data, t_wall wall, int x);
void		draw_ceiling(t_data *data, t_wall wall, int x);
t_direction	analize_direction(float angle);
t_colision	horizontal_intercept(t_data *cube, float angle,
				t_direction direction);
t_colision	vertical_intercept(t_data *data, float ray_angle,
				t_direction direction);

// Destroy and Error handling Functions
void		ft_error(void *pointer, int code);
void		free_all(t_data *cub3d);
void		clear_read(char *line, int fd);
void		free_map(t_data *cub3d);
void		free_double_ptr(void **d_array);
int			exit_window(t_data *cub3d);
void		write_err(char *str);

#endif
