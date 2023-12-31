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
# define IMG_SIZE		2073600

enum e_errs
{
	EXIT,
	ARGS_ERR,
	MALLOC_ERR,
	MAP_ERR,
	IMG_ERR,
};

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_length;
	int		line_color;
}	t_img;

typedef struct s_win
{
	void	*mlx;
	void	*m_win;
	int		width;
	int		height;
}	t_win;

typedef struct s_data
{
	t_map	*map;
	t_img	*img;
	t_win	*win;
}	t_data;

// Initialization Functions
void	map_read(t_data *cub3d, char *filename);
t_bool	read_textures(t_data *cub3d, char *filename, int cardinal);
t_bool	set_floor_ceiling(t_data *cub3d, char *filename);

// Key Parsing Functions
int		key_parse(int key, t_data *cub3d);

// Utils Functions
t_bool	valid_extension(char *file, char *ext);

// Destroy and Error handling Functions
void	ft_error(void *pointer, int code);
void	free_all(t_data *cub3d);
void	clear_read(char *line, int fd);
void	free_map(t_map *map);
void	free_double_ptr(void **d_array);
int		exit_window(t_data *cub3d);
#endif
