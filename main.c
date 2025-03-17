#include "cub.h"

int	ft_exit(t_game *game)
{
	destroy_all(game);
	ft_free(game);
	exit(0);
}

int	render_3d(t_game *game)
{
	ft_key_hook(game);
	mlx_destroy_image(game->mlx, game->image.img_ptr);
	game->image = create_img(game, WIND_W, WIND_H);
	ray_cast(game, game->px, game->py, game->pa);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
	return (0);
}

void	init_image(t_game *game)
{
	if (game->pv == 'S')
		game->pa = (PI / 2);
	else if (game->pv == 'N')
		game->pa = (3 * PI) / 2;
	else if (game->pv == 'E')
		game->pa = 0;
	else if (game->pv == 'W')
		game->pa = PI;
	color_convertor(game);
	game->key = ft_calloc(150, sizeof(char *));
	game->image = create_img(game, WIND_W, WIND_H);
	game->wall_e = new_file_img(game->east, game);
	game->wall_n = new_file_img(game->north, game);
	game->wall_s = new_file_img(game->south, game);
	game->wall_w = new_file_img(game->west, game);
	render_3d(game);
	mlx_put_image_to_window(game->mlx, game->win, game->image.img_ptr, 0, 0);
}

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
	init_image(game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_hook(game->win, 02, (1L << 0), key_press, game);
	mlx_hook(game->win, 03, (1L << 1), key_release, game);
	mlx_loop_hook(game->mlx, render_3d, game);
	mlx_loop(game->mlx);
	destroy_all(game);
	ft_free(game);
	return (0);
}
