/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:49:52 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/14 11:53:05 by pbalbino         ###   ########.fr       */
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
	if (angle > 0 && angle < M_PI)
		direction.is_up = true;
	else
		direction.is_down = true;
	if (angle < (M_PI / 2) || angle > (1.5 * M_PI))
		direction.is_right = true;
	else
		direction.is_left = true;
	return (direction);
}