#include "cub.h"

void	destroy_all(t_game *game)
{
	mlx_destroy_image(game->mlx, game->image.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_e.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_n.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_s.img_ptr);
	mlx_destroy_image(game->mlx, game->wall_w.img_ptr);
	mlx_destroy_window(game->mlx, game->win);
	free(game->key);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	ft_free(t_game *game)
{
	int	i;

	free(game->save);
	free(game->ceiling);
	free(game->floor);
	if (game->east)
		free(game->east);
	if (game->south)
		free(game->south);
	if (game->north)
		free(game->north);
	if (game->west)
		free(game->west);
	i = -1;
	if (game->map)
	{
		if (game->map[++i])
			while (game->map && game->map[i])
				free(game->map[i++]);
		free(game->map);
	}
	destroy_all(game);
	free(game);
}

int	fillemptyspace(t_game *game, int j, char *s, int i)
{
	while (game->map && game->map[++j])
	{
		i = -1;
		s = game->map[j];
		while (s && s[++i])
		{
			if (s[i] == ' ')
				s[i] = '1';
			if (s[i] != '1' && s[i] != '0')
			{
				if ((s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
					&& !game->px && !game->py)
				{
					game->pv = s[i];
					s[i] = '0';
					game->px = i * TILE_SIZE + (TILE_SIZE / 2);
					game->py = j * TILE_SIZE + (TILE_SIZE / 2);
				}
				else
					return (err("Error: invalid map\n"), false);
			}
		}
	}
	return (j);
}

bool	checkwall(char **map, int j)
{
	int	size;
	int	len;

	size = ft_strlen(map[j - 1]) - 1;
	len = ft_strlen(map[j + 1]) - 1;
	if (size > len)
		size = len;
	len = ft_strlen(map[j]) - 1;
	if (map[j][0] != '1' || map[j][len] != '1')
		return (false);
	if (len > size)
	{
		while ((--len > size))
		{
			if (map[j][len] != '1')
				return (false);
		}
	}
	return (true);
}

bool	closedmap(t_game *game, int len)
{
	int		i;
	int		j;
	char	*s;

	j = -1;
	while (game->map && game->map[++j])
	{
		s = game->map[j];
		if ((!j || j == (len - 1)))
		{
			i = -1;
			while (s && s[++i])
				if (s[i] != '1')
					return (err("Error: invalid map\n"), false);
		}
		else
			if (!checkwall(game->map, j))
				return (err("Error: invalid map\n"), false);
	}
	return (true);
}

bool	parse_map(t_game *game)
{
	int	len;

	len = fillemptyspace(game, -1, NULL, 0);
	if (!len)
		return (false);
	if (!closedmap(game, len))
		return (false);
	if (!game->pv)
		return (err("Error: Player is not exist\n"), false);
	return (true);
}
