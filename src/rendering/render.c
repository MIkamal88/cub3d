/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:21:41 by pbalbino          #+#    #+#             */
/*   Updated: 2024/01/14 11:25:40 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int	render_loop(t_data *cub3d)
{
	if (cub3d->is_running == FALSE)
		free_resources(cub3d);
	else
	{
		// check is move player is working
		ray_casting(cub3d);
		render_walls(cub3d);

	}
	return (0);
}