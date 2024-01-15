/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 08:54:41 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 08:54:41 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_texture
{
	char	*path;
	int		cardinal;
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
