/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:20:26 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/29 13:20:26 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

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

#endif
