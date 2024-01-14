/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:27:45 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/14 11:48:36 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	remainder (float x, float y)
{
	float result;

	result = x - (y * (int)(x / y));
	if (result < 0)
		result = result + y;
	return (result);
}

static float	normalize_angle(float angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

void	casting_rays(t_data *cub3d, float ray_angle, int count)
{
	t_colision	horizontal;
	t_colision	vertical;
	t_direction	direction;

	
	}

void	ray_casting(t_data *cub3d)
{
	int		count;
	float	ray_angle;

	count = 0;
	ray_angle = cub3d->player->rotation_angle - (FOV / 2);
	while (count < WINDOW_WIDTH)
	{
		ray_angle = normalize_angle(ray_angle);
		casting_rays(cub3d, ray_angle, count);
		ray_angle = ray_angle + FOV / WINDOW_WIDTH;
		count++;
	}

}