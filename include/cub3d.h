/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 07:29:25 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/20 21:57:19 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdbool.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/libft/includes/get_next_line.h"
//# include "../libs/mlx/linux/mlx.h"
# include "../libs/mlx/mac/mlx.h"
# include "colors.h"
# include "keybinds.h"
//# include "mapping.h"
#include <limits.h>

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	800
# define SCENE_SIZE		WINDOW_WIDTH * WINDOW_HEIGHT
# define TILE_SIZE 		64
# define FOV			1.0471975500000001 // 60 degrees in radians (field of view)

# define MINIMAP_WHITE 0xFFFFFF
# define MINIMAP_RED 0xFF0000
# define MINIMAP_BLACK 0x000000

# define TEXT_COLOR	0xFFFFFF
# define C_WHITE	0xffffff
# define C_GREY		0x303030
# define C_BLACK	0x000000

# define C_RED		0xff0000
# define C_GREEN	0x00ff00
# define C_BLUE		0x0000ff

# define C_YELLOW	0xffff00
# define C_CYAN		0x00ffff
# define C_PINK		0xff00ff

# define C_ORANGY	0xffa500
# define C_BLUEY	0x0492c2

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

typedef struct s_line
{
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	int				delta_x;
	int				delta_y;
	int				side_step;
	float			current_x;
	float			current_y;
	float			inc_x;
	float			inc_y;
	int				color;
}					t_line;

typedef struct s_img
{
	t_line	*line;
	void	*img_ptr;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_length;
	int		line_color;
	t_point	scale;
}	t_img;

typedef struct s_texture
{
	char	*path;
	int		cardinal;
	t_img	*texture_img;
}	t_texture;

typedef struct s_map
{
	int			rows;
	int			x_max;
	int			floor[TOTAL];
	int			ceiling[TOTAL];
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

typedef struct s_rect
{
	int				x;
	int				y;
	int				width;
	int				height;
	int				color;
}					t_rect;





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
	t_point	*pos;
	t_point	*pos_scaled;
	t_coordinate *pos_scaled_game;
	int		cardinal;
	t_bool	set;
	t_movement movement;
	float	rotation_angle;
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

typedef struct s_minimap {
	float			scale;
} t_minimap;

typedef struct s_data
{
	t_map		*map;
	t_img		*scene;
	t_minimap	*minimap;
	//t_img		*minimap;
	t_win		*win;
	t_player	*player;
	int			is_running;
	t_ray		*rays;
	int			*game_color_buffer;

}	t_data;

typedef struct s_colision
{
	float 			distance;
	bool			found_wall;
	float			check_x;
	float			check_y;
	bool			is_horizontal;
	t_coordinate	next_interception;
	t_coordinate    intercept;
	t_coordinate	wall_hit;
	t_coordinate	step;

} t_colision;

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
void	init_player(t_data *cub3d);
void	map_read(t_data *cub3d, char *filename);
t_bool	read_textures(t_data *cub3d, char *filename, int cardinal);
t_bool	set_floor_ceiling(t_data *cub3d, char *filename);
t_bool	load_grid(t_data *cub3d, char *filename);
t_bool	check_assets(t_data *cub3d);
t_bool	is_closed(t_data *cub3d, int x, int y);

// Drawing
void	pixel_put(t_img *img, int x, int y, int color);
int	create_trgb(int r, int g, int b);
int	get_texture_color(t_img *texture, int x, int y);
int	pixel_get(t_img *img, int x, int y);
void	render_player(t_data *cub3d);
t_line	*start_line(t_point p0, t_point p1, int color);
void	draw_line(t_img *img, t_line *line);
void	scale_line(t_img *img, t_map *map, t_line *line);
void	render_minimap(t_data *cub3d);
void	mm_single_wall(t_data *cub3d, int *x, int *y);
void	print_text(t_data *cub3d);

// Key Parsing Functions
int		key_parse(int key, t_data *cub3d);
void	move_player(t_data *cub3d, int key);

// Utils Functions
t_bool	map_start(char *line);
t_bool	valid_extension(char *file, char *ext);
void	swap_points(t_point *p0, t_point *p1);
int		ft_abs(int n);

// Destroy and Error handling Functions
void	ft_error(void *pointer, int code);
void	free_all(t_data *cub3d);
void	clear_read(char *line, int fd);
void	free_map(t_map *map);
void	free_double_ptr(void **d_array);
int		exit_window(t_data *cub3d);

// Raycasting
t_direction analize_direction(float angle);
void	ray_casting(t_data *cub3d);
int		render_loop(t_data *cub3d);
void	render_walls(t_data *cub3d);
t_colision	horizontal_intercept(t_data *cube, float angle, t_direction direction);
t_colision	vertical_intercept(t_data *data, float ray_angle, t_direction direction);
void	get_current_rotation_angle(t_data *cub3d);
int	key_pressed(int keycode, t_data *data);
int	key_released(int keycode, t_data *data);
bool	has_wall(t_data *data, float x, float y);
void	render_map(t_data *data);
void	analyze_colision(t_data *data, t_colision *colision, bool direction);


// Textures
bool	load_texture(t_data *cube, int cardinal);

#endif
