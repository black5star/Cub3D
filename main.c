#include "cub.h"

int	ft_exit(t_game *game)
{
	ft_free(game);
	exit(0);
}

void	fill_square(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	j = -1;
	while (++j < TILE_SIZE)
	{
		i = -1;
		while(++i < TILE_SIZE)
			mlx_pixel_put(game->mlx, game->win, x * TILE_SIZE + i, y * TILE_SIZE + j, color);
	}
}

void	draw_player(t_game *game, int x, int y, int color)
{
	int i;
	int j = 0;

	while (++j < TILE_SIZE / 2)
	{
		i = 0;
		while(++i < TILE_SIZE / 2)
			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
	}
}

void	render_map(t_game *game)
{
	int i;
	int j = -1;

	while(game->map && game->map[++j])
	{
		i = -1;
		while(game->map[j][++i])
		{
			if(game->map[j][i] == '1')
				fill_square(game, i, j, 0x2109db);
			else
				fill_square(game, i, j, 0xffffff);
			if (game->map[j][i] == game->pv)
			{
				// printf("px %d and py %d\n", game->px, game->py);
				draw_player(game, game->px, game->py, PLAYER_COLOR);
				game->map[j][i] = '0';
			}
		}
	}
}

void	go_up(t_game *game)
{
	// int x;
	// int y;

	// x = game->px / TILE_SIZE;
	// y = game->py / TILE_SIZE;
	if (1)
	{
		draw_player(game, game->px, game->py, 0xffffff);
		game->py -= 5;
		// game->map[game->py][game->px] = 'P';
		// game->map[game->py + 1][game->px] = '0';
		// render_map(game);
		draw_player(game, game->px, game->py, PLAYER_COLOR);
	}
}

void	go_down(t_game *game)
{
	// int x;
	// int y;

	// x = game->px / TILE_SIZE;
	// y = game->py / TILE_SIZE;
	if (1)
	{
		draw_player(game, game->px, game->py, 0xffffff);
		game->py += 5;
		// game->map[game->py][game->px] = 'P';
		// game->map[game->py - 1][game->px] = '0';
		// render_map(game);
		draw_player(game, game->px, game->py, PLAYER_COLOR);
	}
}

void	to_right(t_game *game)
{
	// int x;
	// int y;

	// x = game->px / TILE_SIZE;
	// y = game->py / TILE_SIZE;
	if (1)
	{
		draw_player(game, game->px, game->py, 0xffffff);
		game->px += 5;
		// game->map[game->py][game->px] = 'P';
		// game->map[game->py][game->px - 1] = '0';
		// render_map(game);
		draw_player(game, game->px, game->py, PLAYER_COLOR);
	}
}

void	to_left(t_game *game)
{
	// int x;
	// int y;

	// x = game->px / TILE_SIZE;
	// y = game->py / TILE_SIZE;
	if (1)
	{
		draw_player(game, game->px, game->py, 0xffffff);
		game->px -= 5;
		// game->map[game->py][game->px] = 'P';
		// game->map[game->py][game->px + 1] = '0';
		// render_map(game);
		draw_player(game, game->px, game->py, PLAYER_COLOR);
	}
}

int	ft_key_hook(int key_code, t_game *game)
{
	if (key_code == 65307)
		ft_exit(game);
	if (key_code == 'w')
		go_up(game);
	if (key_code == 's')
		go_down(game);
	if (key_code == 'd')
		to_right(game);
	if (key_code == 'a')
		to_left(game);
	// if (key_code == 65361)
	// 	to_left(game);
	// if (key_code == 65363)
	// 	to_left(game);
	return (1);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	if (!game)
		return (1);
	if (!parse_map(game))
		return (ft_free(game), 1);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIND_W, WIND_H, "Black Star");
	render_map(game);
	mlx_hook(game->win, 2, (1L << 0), ft_key_hook, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop(game->mlx);
	ft_free(game);
	return (0);
}
