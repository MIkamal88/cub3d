/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:27:45 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/14 23:02:43 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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

	printf("\nray angle %f", ray_angle);
	//cub3d->player->pos_scaled_game->x = cub3d->player->pos_scaled->x * 5;
	//cub3d->player->pos_scaled_game->y = cub3d->player->pos_scaled->y * 5;

	direction = analize_direction(ray_angle);
	horizontal = horizontal_intercept(cub3d, ray_angle, direction);
	vertical = vertical_intercept(cub3d, ray_angle, direction);
	if (vertical.distance < horizontal.distance)
	{
		cub3d->rays[count].distance = vertical.distance;
		cub3d->rays[count].hit_x = horizontal.wall_hit.x;
		cub3d->rays[count].hit_y = horizontal.wall_hit.y;
		cub3d->rays[count].is_up = true;
		printf("rays count=%d distance=%f hit_x=%f hit_y=%f is_up=%d\n", count, cub3d->rays[count].distance, cub3d->rays[count].hit_x, cub3d->rays[count].hit_y, 1);
	}
	else
	{
		cub3d->rays[count].distance = horizontal.distance;
		cub3d->rays[count].hit_x = vertical.wall_hit.x;
		cub3d->rays[count].hit_y = vertical.wall_hit.y;
		cub3d->rays[count].is_up = false;
		printf("rays count=%d distance=%f hit_x=%f hit_y=%f is_up=%d\n", count, cub3d->rays[count].distance, cub3d->rays[count].hit_x, cub3d->rays[count].hit_y, 1);
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
	printf("\nrotation_angle %f", cub3d->player->rotation_angle);
	while (count < WINDOW_WIDTH)
	{
		ray_angle = normalize_angle(ray_angle);
		single_ray(cub3d, ray_angle, count);
		ray_angle = ray_angle + FOV / WINDOW_WIDTH;
		count++;
	}
}