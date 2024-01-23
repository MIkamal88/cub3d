/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:32:35 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/20 22:01:47 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_push(int keycode, t_data *cube)
{
	if (keycode == KEY_ESC)
	{
		free_all(cube);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_W || keycode == KEY_UP)
		cube->player->movement.walk_direction = FORWARD;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cube->player->movement.walk_direction = BACKWARD;
	else if (keycode == KEY_A)
		cube->player->movement.side_direction = LEFT;
	else if (keycode == KEY_D)
		cube->player->movement.side_direction = RIGHT;
	else if (keycode == KEY_RIGHT)
		cube->player->movement.turn_direction = CLOCKWISE;
	else if (keycode == KEY_LEFT)
		cube->player->movement.turn_direction = ANTICLOCKWISE;
	ft_bzero(cube->scene->addr, SCENE_SIZE * 4);
	return (EXIT_SUCCESS);
}

int	key_release(int keycode, t_data *cube)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		cube->player->movement.walk_direction = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		cube->player->movement.walk_direction = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		cube->player->movement.side_direction = 0;
	else if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
		cube->player->movement.turn_direction = 0;
	return (EXIT_SUCCESS);
}
