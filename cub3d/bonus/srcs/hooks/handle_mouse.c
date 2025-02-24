#include "cub3d_bonus.h"

/*
Get the current mouse position -> Get the center of the window
Calculate the horizontal mouse movement ->
Apply the mouse movement to rotate the player -> 
Re-center the mouse in the window to continue tracking movement
*/

void	handle_mouse_movement(t_game *game)
{
	int		mouse_x;
	int		mouse_y;
	double	mouse_delta;
	int		win_center_x;

	mlx_mouse_get_pos(game->mlx, game->window->ptr, &mouse_x, &mouse_y);
	win_center_x = game->window->size.x / 2;
	mouse_delta = mouse_x - win_center_x;
	if (mouse_delta > 5) // Here we can adjust the threshold for smoother rotation
		rotate_left(&game->player, game->player.rot_speed, 1);
	else if (mouse_delta < -5)
		rotate_right(&game->player, game->player.rot_speed, 1);
	mlx_mouse_move(game->mlx, game->window->ptr, win_center_x, win_center_x);
}

