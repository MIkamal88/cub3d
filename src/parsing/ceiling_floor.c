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

#include "../../include/cub3d.h"

static t_bool	validate_color(t_data *cub3d, char *line, char type, int fd);
static t_bool	set_color(t_data *cub3d, char *colors, char type);

t_bool	set_floor_ceiling(t_data *cub3d, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (!line || fd < 0)
	{
		clear_read(line, fd);
		ft_error(cub3d, MAP_ERR);
	}
	while (line)
	{
		if (ft_strnstr(line, "F ", ft_strlen(line)))
			if (!validate_color(cub3d, line, 'F', fd))
				return (FALSE);
		if (ft_strnstr(line, "C ", ft_strlen(line)))
			if (!validate_color(cub3d, line, 'C', fd))
				return (FALSE);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (TRUE);
}

static t_bool	validate_color(t_data *cub3d, char *line, char type, int fd)
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
			else if (set_color(cub3d, line_split[i + 1], type))
			{
				free_double_ptr((void **)line_split);
				return (TRUE);
			}
		}
	}
	if (line_split)
		free_double_ptr((void **)line_split);
	clear_read(line, fd);
	return (FALSE);
}

static t_bool	check_rgb(t_data *cub3d, char **colors, char type)
{
	int	i;

	i = -1;
	while (colors[++i] && i < 3)
	{
		if (!ft_isdigit(colors[i][0]))
		{
			if (colors)
				free_double_ptr((void **)colors);
			return (FALSE);
		}
	}
	if (i != 3)
	{
		if (colors)
			free_double_ptr((void **)colors);
		return (FALSE);
	}
	if (type == 'F')
		cub3d->map->floor_set = TRUE;
	else if (type == 'C')
		cub3d->map->ceiling_set = TRUE;
	return (TRUE);
}

static t_bool	comma_check(char *colors)
{
	int	i;
	int	comma_count;

	i = -1;
	comma_count = 0;
	while (colors[++i])
	{
		if (colors[i] == ',')
			comma_count++;
		if (colors[i + 1])
			if (colors[i] == ',' && colors[i + 1] == ',' )
				return (FALSE);
	}
	if (comma_count > 2)
		return (FALSE);
	return (TRUE);
}

static t_bool	set_color(t_data *cub3d, char *colors, char type)
{
	int		i;
	int		j;
	char	**color_split;

	i = -1;
	j = 0;
	if (!comma_check(colors))
		return (FALSE);
	color_split = ft_split(colors, ',');
	if (!check_rgb(cub3d, color_split, type))
		return (FALSE);
	while (color_split[++i])
	{
		if (ft_atoi(color_split[i]) > 255 || ft_atoi(color_split[i]) < 0)
			return (FALSE);
		if (type == 'F')
			cub3d->map->floor[j] = ft_atoi(color_split[i]);
		else
			cub3d->map->ceiling[j] = ft_atoi(color_split[i]);
		j++;
	}
	if (color_split)
		free_double_ptr((void **)color_split);
	return (TRUE);
}
