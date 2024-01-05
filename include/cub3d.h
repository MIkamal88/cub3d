/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 07:29:25 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/29 07:29:25 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../libs/libft/includes/libft.h"
# include "../libs/libft/includes/get_next_line.h"
# include "../libs/mlx/linux/mlx.h"
/* #include "../libs/mlx/mac/mlx.h" */
# include "colors.h"
# include "keybinds.h"
# include "mapping.h"

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define SCENE_SIZE	2073600

# define TEXT_COLOR		0xFFFFFF
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

enum e_errs
{
	EXIT,
	ARGS_ERR,
	MALLOC_ERR,
	MAP_ERR,
	IMG_ERR,
};

typedef struct s_line
{
	t_point	start;
	t_point	end;
	float	dx;
	float	dy;
	float	decision;
	int		color;
}	t_line;

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

typedef struct s_win
{
	void	*mlx;
	void	*m_win;
	int		width;
	int		height;
}	t_win;

typedef struct s_player
{
	t_point	*pos;
	t_point	*pos_scaled;
	int		cardinal;
	t_bool	set;
}	t_player;

typedef struct s_data
{
	t_map		*map;
	t_img		*scene;
	t_img		*minimap;
	t_win		*win;
	t_player	*player;
}	t_data;

// Initialization Functions
void	map_read(t_data *cub3d, char *filename);
t_bool	read_textures(t_data *cub3d, char *filename, int cardinal);
t_bool	set_floor_ceiling(t_data *cub3d, char *filename);
t_bool	load_grid(t_data *cub3d, char *filename);
void	init_player(t_data *cub3d);
t_line	*start_line(t_point p0, t_point p1, int color);

// Drawing
void	pixel_put(t_img *img, int x, int y, int color);
void	player_arrow(t_img *map, t_player *p, int i);
t_line	*start_line(t_point p0, t_point p1, int color);
void	draw_line(t_img *img, t_line *line);
void	scale_line(t_img *img, t_map *map, t_line *line);
void	render_minimap(t_data *cub3d);
void	print_text(t_data *cub3d);

// Key Parsing Functions
int		key_parse(int key, t_data *cub3d);
void	move_player(t_data *cub3d, int key);

// Utils Functions
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
#endif
