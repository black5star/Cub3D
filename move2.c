#include "cub.h"

int	wall_checker(t_game *game, int x, int y)
{
	int	i;
	int	j;

	if (x <= 0 || y <= 0)
		return (1);
	i = x / TILE_SIZE;
	j = y / TILE_SIZE;
	if (game->map[j] && game->map[j][i])
	{
		if (game->map[j][i] == '1')
			return (1);
	}
	return (0);
}

int	can_move(t_game *game, int x, int y)
{
	int	i;
	int	j;

	j = y - (TILE_SIZE / 4);
	while (j <= (y + (TILE_SIZE / 4)))
	{
		i = x - (TILE_SIZE / 4);
		while (i <= (x + (TILE_SIZE / 4)))
		{
			if (wall_checker(game, i, j))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 65307)
		exit(ft_exit(game));
	if (keycode == 65363)
		game->key[130] = 1;
	if (keycode == 65361)
		game->key[131] = 1;
	if (keycode <= 127)
		game->key[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 65363)
		game->key[130] = 0;
	if (keycode == 65361)
		game->key[131] = 0;
	if (keycode <= 127)
		game->key[keycode] = 0;
	return (0);
}
