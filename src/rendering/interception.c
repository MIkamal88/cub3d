/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interception.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 21:28:01 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/20 21:28:59 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_colision	vertical_intercept(t_data *data, float ray_angle,
		t_direction direction)
{
	t_colision	colision;

	colision.found_wall = false;
	colision.wall_hit.x = 0;
	colision.wall_hit.y = 0;
	colision.distance = INT_MAX;
	colision.is_horizontal = false;
	colision.intcpt.x = floor(data->player->pos_game->x / TILE_SIZE) * TILE_SIZE;
	if (direction.is_right)
		colision.intcpt.x += TILE_SIZE;
	colision.intcpt.y = data->player->pos_game->y + (colision.intcpt.x
			- data->player->pos_game->x) * tan(ray_angle);
	colision.step.x = TILE_SIZE;
	if (direction.is_left)
		colision.step.x = colision.step.x * -1;
	colision.step.y = TILE_SIZE * tan(ray_angle);
	if (direction.is_up && colision.step.y > 0)
		colision.step.y = colision.step.y * -1;
	if (direction.is_down && colision.step.y < 0)
		colision.step.y *= -1;
	colision.next_interception.x = colision.intcpt.x;
	colision.next_interception.y = colision.intcpt.y;
	analyze_colision(data, &colision, direction.is_left);
	return (colision);
}

t_colision	horizontal_intercept(t_data *data, float ray_angle,
	t_direction direction)
{
	t_colision	colision;

	colision.found_wall = false;
	colision.wall_hit.x = 0;
	colision.wall_hit.y = 0;
	colision.distance = INT_MAX;
	colision.is_horizontal = true;
	colision.intcpt.y = floor(data->player->pos_game->y / TILE_SIZE) * TILE_SIZE;
	if (direction.is_down)
		colision.intcpt.y += TILE_SIZE;
	colision.intcpt.x = data->player->pos_game->x + (colision.intcpt.y
													 - data->player->pos_game->y) / tan(ray_angle);
	colision.step.y = TILE_SIZE;
	if (direction.is_up)
		colision.step.y = colision.step.y * -1;
	colision.step.x = TILE_SIZE / tan(ray_angle);
	if (direction.is_left && colision.step.x > 0)
		colision.step.x = colision.step.x * -1;
	if (direction.is_right && colision.step.x < 0)
		colision.step.x = colision.step.x * -1;
	colision.next_interception.x = colision.intcpt.x;
	colision.next_interception.y = colision.intcpt.y;
	analyze_colision(data, &colision, direction.is_up);
	return (colision);
}
	//printf("\n player hor xScaled=%f yScaled=%f",data->player->pos_game->x, data->player->pos_game->y );
