/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:32:35 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/14 21:32:54 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"



int	key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		free_all(data);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_W || keycode == KEY_UP)
		data->player->movement.walk_direction = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		data->player->movement.walk_direction = -1;
	else if (keycode == KEY_A)
		data->player->movement.side_direction = 1;
	else if (keycode == KEY_D)
		data->player->movement.side_direction = -1;
	else if (keycode == KEY_RIGHT)
		data->player->movement.turn_direction = 1;
	else if (keycode == KEY_LEFT)
		data->player->movement.turn_direction = -1;
	//ft_bzero(data->scene->addr, SCENE_SIZE * 8);
	//ft_bzero(data->minimap->addr, (data->minimap->h * data->minimap->w) * 4);
	return (EXIT_SUCCESS);
}

int	key_released(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		data->player->movement.walk_direction = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		data->player->movement.walk_direction = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		data->player->movement.side_direction = 0;
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		data->player->movement.turn_direction = 0;
	return (EXIT_SUCCESS);
}