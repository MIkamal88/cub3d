/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:49:52 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/15 14:21:23 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_direction analize_direction(float angle)
{
	t_direction direction;

	direction.is_up = false;
	direction.is_down = false;
	direction.is_left = false;
	direction.is_right = false;
	if( angle > M_PI && angle < 2 * M_PI) {
		direction.is_up = true;
	}else{
		direction.is_up = false;
	}
	if(angle < 0.5 * M_PI || angle > 1.5* M_PI){
		direction.is_right = true;
	}else
	{
		direction.is_right = false;
	}
	direction.is_left = ! direction.is_right;
	return (direction);
}

bool	is_wall(t_data *cube, float x, float y)
{
	int map_x;
	int map_y;

	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	//printf("\n is_wall: map_x: %d, map_y: %d x_max: %d rows: %d", map_x, map_y, cube->map->x_max, cube->map->rows);
	if (map_x < 0 || map_x >= cube->map->x_max || map_y < 0 || map_y >= cube->map->rows)
		return (true);
	if (cube->map->grid[map_y][map_x].type == WALL) // if we consider spaces as wall we need to add this condition here;
		return (true);
	return (false);

}

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
//	printf("has_wall x=%d y=%d wall=%d\n",map_grid_x, map_grid_y,  data->map->grid[map_grid_y][map_grid_x].type);
	return (data->map->grid[map_grid_y][map_grid_x].type == WALL
	|| data->map->grid[map_grid_y][map_grid_x].type == EMPTY
	);
}

float	wall_hit_distance(float x0, float y0, float x1, float y1)
{
	float result = 0;

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
		//	printf("\nhas_wall %f %f", colision->next_interception.x, colision->next_interception.y);
			colision->wall_hit.x = colision->next_interception.x;
			colision->wall_hit.y = colision->next_interception.y;
			colision->found_wall = true;
			break ;
		}
		else
		{
		//	printf("\n no wall step x %f step y %f", colision->step.x, colision->step.y);
			colision->next_interception.x += colision->step.x;
			colision->next_interception.y += colision->step.y;
		}
	}
	if (colision->found_wall) {
	//	printf("\nget_hit_distance px %f py %f wall hit x %f  wall hit y %f \n",data->player->pos_scaled_game->x,
	//		   data->player->pos_scaled_game->y, colision->wall_hit.x, colision->wall_hit.y);
		colision->distance = wall_hit_distance(data->player->pos_scaled_game->x,
											   data->player->pos_scaled_game->y, colision->wall_hit.x,
											   colision->wall_hit.y);
	}
}


t_colision	vertical_intercept(t_data *data,float ray_angle, t_direction direction)
{
	t_colision	colision;

	colision.found_wall = false;
	colision.wall_hit.x = 0;
	colision.wall_hit.y = 0;
	colision.distance = INT_MAX;
	colision.is_horizontal = false;
	colision.intercept.x = floor(data->player->pos_scaled_game->x / TILE_SIZE) * TILE_SIZE;
	if (direction.is_right)
		colision.intercept.x += TILE_SIZE;
	colision.intercept.y = data->player->pos_scaled_game->y + (colision.intercept.x
			- data->player->pos_scaled_game->x) * tan(ray_angle);
	colision.step.x = TILE_SIZE;
	if (direction.is_left)
		colision.step.x = colision.step.x * -1;
	colision.step.y = TILE_SIZE * tan(ray_angle);
	if (direction.is_up && colision.step.y > 0)
		colision.step.y = colision.step.y * -1;
	if (direction.is_down && colision.step.y < 0)
		colision.step.y *= -1;
	colision.next_interception.x = colision.intercept.x;
	colision.next_interception.y = colision.intercept.y;
	analyze_colision(data, &colision, direction.is_left);
	return (colision);
}



t_colision	horizontal_intercept(t_data *data, float ray_angle, t_direction direction)
{
	t_colision	colision;

	colision.found_wall = false;
	colision.wall_hit.x = 0;
	colision.wall_hit.y = 0;
	colision.distance = INT_MAX;
	colision.is_horizontal = true;
	printf("\n player hor xScaled=%f yScaled=%f",data->player->pos_scaled_game->x, data->player->pos_scaled_game->y );
	colision.intercept.y = floor(data->player->pos_scaled_game->y / TILE_SIZE) * TILE_SIZE;
	if (direction.is_down)
		colision.intercept.y += TILE_SIZE;
	colision.intercept.x = data->player->pos_scaled_game->x + (colision.intercept.y
			- data->player->pos_scaled_game->y) / tan(ray_angle);
	colision.step.y = TILE_SIZE;
	if (direction.is_up)
		colision.step.y = colision.step.y * -1;
	colision.step.x = TILE_SIZE / tan(ray_angle);
	if (direction.is_left && colision.step.x > 0)
		colision.step.x = colision.step.x * -1;
	if (direction.is_right && colision.step.x < 0)
		colision.step.x = colision.step.x * -1;
	colision.next_interception.x = colision.intercept.x;
	colision.next_interception.y = colision.intercept.y;
	analyze_colision(data, &colision, direction.is_up);
	return (colision);
}

float	horizontal_interceptOld(t_data *cube, float angle, t_direction direction)
{
	t_colision		horizontal;
	t_coordinate	intercept;
	t_coordinate	step;
	t_coordinate	next;

	horizontal.found_wall = false;
	printf("\n player vert xScaled=%f yScaled=%f",cube->player->pos_scaled_game->x, cube->player->pos_scaled_game->y );
	intercept.y = floor(cube->player->pos_scaled->y / TILE_SIZE) * TILE_SIZE;
	if (direction.is_down)
		intercept.y = intercept.y + TILE_SIZE;
	intercept.x = cube->player->pos_scaled->x + ((intercept.y - cube->player->pos_scaled->y) / tan(angle));
	step.y = TILE_SIZE;
	if (direction.is_up)
		step.y = step.y -1;
	step.x = TILE_SIZE / tan(angle);
	if (direction.is_left && step.x > 0)
		step.x = step.x -1;
	if (direction.is_right && step.x < 0)
		step.x = step.x -1;
	next.x = intercept.x;
	next.y = intercept.y;
	if (direction.is_up)
		next.y--;
	while (next.x >= 0 && next.x <= WINDOW_WIDTH && next.y >= 0 && next.y <= WINDOW_HEIGHT)
	{
		if (is_wall(cube, next.x, next.y))
		{
			horizontal.found_wall = true;
			horizontal.intercept.x = next.x;
			horizontal.intercept.y = next.y;
			break ;
		}
		else
		{
			next.x = next.x + step.x;
			next.y = next.y + step.y;
		}
	}
	return (horizontal.intercept.x);
}
// float	vertical_intercept(t_data *cube, float angle, t_direction direction)
// {
// 	t_colision		vertical;
// 	t_coordinate	intercept;
// 	t_coordinate	step;
// 	t_coordinate	next;

// 	vertical.found_wall = false;
// 	intercept.x = floor(cube->player->pos->x / TILE_SIZE) * TILE_SIZE;
// 	if (direction.is_right)
// 		intercept.x = intercept.x + TILE_SIZE;
// 	intercept.y = cube->player->pos->y + ((intercept.x - cube->player->pos->x) * tan(angle));
// 	step.x = TILE_SIZE;
// 	if (direction.is_left)
// 		step.x = step.x -1;
// 	step.y = TILE_SIZE * tan(angle);
// 	if (direction.is_up && step.y > 0)
// 		step.y = step.y -1;
// 	if (direction.is_down && step.y < 0)
// 		step.y = step.y -1;
// 	next.x = intercept.x;
// 	next.y = intercept.y;
// 	if (direction.is_left)
// 		next.x--;
// 	while (next.x >= 0 && next.x <= WINDOW_WIDTH && next.y >= 0 && next.y <= WINDOW_HEIGHT)
// 	{
// 		if (is_wall(cube, next.x, next.y))
// 		{
// 			vertical.found_wall = true;
// 			vertical.x = next.x;
// 			vertical.y = next.y;
// 			break ;
// 		}
// 		else
// 		{
// 			next.x = next.x + step.x;
// 			next.y = next.y + step.y;
// 		}
// 	}
// 	return (vertical.y);
// }
