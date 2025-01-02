
#include "cub.h"

void    ft_free(t_game *game)
{
    int i;

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
    free(game);
}

int main(int ac, char **av)
{
    t_game  *game;

    if (ac != 2)
        return (1);
    game = parsing(av[1]);
    if (!game)
        return (1);
    if(!parse_map(game))
        return(ft_free(game), 1);
    printf("good map\n");
    // game->mlx = mlx_init();
    // game->win = mlx_new_window(game->mlx, game->win_h, game->win_w, "Cub3D");
    // mlx_loop(game->mlx);
    ft_free(game);
    return(0);
}
