#include "cub3d_bonus.h"

/*
This function tracks the horizontal movement of the mouse and applies rotation
to the player accordingly. The rotation speed is dynamically adjusted based
on the distance of the mouse from the center of the window.

If the mouse moves beyond a certain threshold, the rotation speed is set 
proportionally to the displacement. Otherwise, a damping effect is applied 
to gradually reduce the rotation speed, ensuring smooth deceleration when 
the mouse stops moving.

The function also recenters the mouse when it enters the dead zone to 
prevent uncontrolled drift.
*/

void	handle_mouse_movement(t_game *game, t_window *window)
{
	static double	rotation_speed;
	t_point			mouse;
	int				win_center_x;
	double			mouse_delta;
	double			sensitivity = 0.00002;

	mlx_mouse_get_pos(game->mlx, window->ptr, &mouse.x, &mouse.y);
	win_center_x = window->size.x / 2;
	mouse_delta = mouse.x - win_center_x;

	if (fabs(mouse_delta) > window->size.x / 5)
		rotation_speed = mouse_delta * sensitivity * game->player.rot_speed;
	else
	{
		rotation_speed *= 0.9;
		if (fabs(rotation_speed) < 0.0001)
			rotation_speed = 0;
	}
	if (rotation_speed > 0)
		rotate_left(&game->player, rotation_speed, 1);
	else if (rotation_speed < 0)
		rotate_right(&game->player, -rotation_speed, 1);
	if (fabs(mouse_delta) <= window->size.x / 5)
		mlx_mouse_move(game->mlx, window->ptr, win_center_x,
						window->size.y / 2);
}
