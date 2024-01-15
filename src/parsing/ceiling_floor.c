/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 15:19:43 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/15 10:13:29 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	validate_color(t_data *cub3d, char *line, char type);
t_bool	set_color(t_data *cub3d, char *colors, char type);

t_bool	set_floor_ceiling(t_data *cub3d, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
		ft_error(cub3d, MAP_ERR);
	while (line)
	{
		if (ft_strnstr(line, "F ", ft_strlen(line)))
			if (!validate_color(cub3d, line, 'F'))
				return (FALSE);
		if (ft_strnstr(line, "C ", ft_strlen(line)))
			if (!validate_color(cub3d, line, 'C'))
				return (FALSE);
		free(line);
		line = get_next_line(fd);
	}
	return (TRUE);
}

t_bool	validate_color(t_data *cub3d, char *line, char type)
{
	int		i;
	char	**line_split;

	i = -1;
	line_split = ft_split(line, ' ');
	while (line_split[++i])
	{
		if ((ft_strncmp(line_split[i], "F", 1) == 0 && type == 'F')
			|| (ft_strncmp(line_split[i], "C", 1) == 0 && type == 'C'))
		{
			if (!line_split[i + 1])
				free_double_ptr((void **)line_split);
			else
			{
				if (set_color(cub3d, line_split[i + 1], type))
				{
					free_double_ptr((void **)line_split);
					return (TRUE);
				}
			}
		}
	}
	if (line_split)
		free_double_ptr((void **)line_split);
	return (FALSE);
}

t_bool	set_color(t_data *cub3d, char *colors, char type)
{
	int		i;
	int		j;
	char	**color_split;

	i = -1;
	j = 0;
	color_split = ft_split(colors, ',');
	while (color_split[++i])
	{
		if (ft_isdigit(color_split[i][0]))
		{
			if (ft_atoi(color_split[i]) > 255 || ft_atoi(color_split[i]) < 0)
				return (FALSE);
			if (type == 'F')
				cub3d->map->floor[j] = ft_atoi(color_split[i]);
			else
				cub3d->map->ceiling[j] = ft_atoi(color_split[i]);
			j++;
		}
		else
			return (FALSE);
	}
	if (color_split)
		free_double_ptr((void **)color_split);
	return (TRUE);
}
