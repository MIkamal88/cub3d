/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybinds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 08:32:35 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/14 11:17:32 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_parse(int key, t_data *cub3d)
{
	if (key == KEY_ESC)
	{
		free_all(cub3d);
		exit(EXIT_SUCCESS);
	}
	if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D
		|| key == KEY_LEFT || key == KEY_RIGHT)
		move_player(cub3d, key);
	ft_bzero(cub3d->scene->addr, SCENE_SIZE * 4);
	ft_bzero(cub3d->minimap->addr, (cub3d->minimap->h * cub3d->minimap->w) * 4);
	render_minimap(cub3d);
	return (0);
}
