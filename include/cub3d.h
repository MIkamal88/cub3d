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

# include "../libs/libft/includes/libft.h"
# include "../libs/libft/includes/get_next_line.h"
# include "structs.h"
# include "colors.h"
# include "keybinds.h"
# include <math.h>
# include <limits.h>

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
