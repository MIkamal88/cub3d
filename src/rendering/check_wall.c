/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 11:55:35 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/21 11:58:00 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	has_wall(t_data *data, float x, float y)
{
	int	map_grid_x;
	int	map_grid_y;

	if (!map_limits(data, x, y))
		return (true);
	map_grid_x = floor(x / TILE_SIZE);
	map_grid_y = floor(y / TILE_SIZE);
	return (data->map->grid[map_grid_y][map_grid_x].type == WALL
	|| data->map->grid[map_grid_y][map_grid_x].type == EMPTY
	);
}

float	wall_hit_distance(float x0, float y0, float x1, float y1)
{
	float	result;

	result = sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
	return (result);
}
