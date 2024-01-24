/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:27:45 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/22 21:57:52 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

static void	single_ray(t_data *cub3d, float ray_angle, int count)
{
	t_colision	horizontal;
	t_colision	vertical;
	t_direction	direction;

	ray_angle = normalize_angle(ray_angle);
	direction = analize_direction(ray_angle);
	horizontal = horizontal_intercept(cub3d, ray_angle, direction);
	vertical = vertical_intercept(cub3d, ray_angle, direction);
	if (vertical.distance < horizontal.distance)
	{
		cub3d->rays[count].distance = vertical.distance;
		cub3d->rays[count].hit_x = vertical.wall_hit.x;
		cub3d->rays[count].hit_y = vertical.wall_hit.y;
		cub3d->rays[count].is_up = true;
	}
	else
	{
		cub3d->rays[count].distance = horizontal.distance;
		cub3d->rays[count].hit_x = horizontal.wall_hit.x;
		cub3d->rays[count].hit_y = horizontal.wall_hit.y;
		cub3d->rays[count].is_up = false;
	}
	cub3d->rays[count].angle = ray_angle;
	cub3d->rays[count].direction = direction;
}

void	ray_casting(t_data *cub3d)
{
	int		count;
	float	ray_angle;

	count = 0;
	ray_angle = cub3d->player->rotation_angle - (FOV / 2);
	while (count < WINDOW_WIDTH)
	{
		single_ray(cub3d, ray_angle, count);
		ray_angle = ray_angle + FOV / WINDOW_WIDTH;
		count++;
	}
}
