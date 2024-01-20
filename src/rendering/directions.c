/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:49:52 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/20 21:29:55 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_direction	analize_direction(float angle)
{
	t_direction	direction;

	direction.is_up = false;
	direction.is_down = false;
	direction.is_left = false;
	direction.is_right = false;
	if (angle > M_PI && angle < 2 * M_PI)
		direction.is_up = true;
	else
		direction.is_up = false;
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
		direction.is_right = true;
	else
		direction.is_right = false;
	direction.is_left = ! direction.is_right;
	direction.is_down = ! direction.is_up;
	return (direction);
}

bool	is_wall(t_data *cube, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= cube->map->x_max || map_y < 0
		|| map_y >= cube->map->rows)
		return (true);
	if (cube->map->grid[map_y][map_x].type == WALL)
		return (true);
	return (false);
}
// if we consider spaces as wall we need to add this condition above;

bool	map_limits(t_data *data, float x, float y)
{
	return (x >= 0 && x < data->map->x_max * TILE_SIZE && y >= 0
		&& y < data->map->rows * TILE_SIZE);
}

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
//	printf("has_wall x=%d y=%d wall=%d\n",map_grid_x, map_grid_y,  data->map->grid[map_grid_y][map_grid_x].type);

float	wall_hit_distance(float x0, float y0, float x1, float y1)
{
	float	result;

	result = sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
	return (result);
}

void	analyze_colision(t_data *data, t_colision *colision, bool direction)
{
	while (map_limits(data, colision->next_interception.x,
			colision->next_interception.y))
	{
		colision->check_x = colision->next_interception.x;
		colision->check_y = colision->next_interception.y;
		if (direction && !colision->is_horizontal)
			colision->check_x--;
		if (direction && colision->is_horizontal)
			colision->check_y--;
		if (has_wall(data, colision->check_x, colision->check_y))
		{
			colision->wall_hit.x = colision->next_interception.x;
			colision->wall_hit.y = colision->next_interception.y;
			colision->found_wall = true;
			break ;
		}
		else
		{
			colision->next_interception.x += colision->step.x;
			colision->next_interception.y += colision->step.y;
		}
	}
	if (colision->found_wall)
	{
		colision->distance = wall_hit_distance(data->player->pos_scaled_game->x,
				data->player->pos_scaled_game->y, colision->wall_hit.x,
				colision->wall_hit.y);
	}
}

/*
	printf("\nhas_wall %f %f", colision->next_interception.x, colision->next_interception.y);
	printf("\nget_hit_distance px %f py %f wall hit x %f  wall hit y %f \n",data->player->pos_scaled_game->x,
		   data->player->pos_scaled_game->y, colision->wall_hit.x, colision->wall_hit.y);
*/