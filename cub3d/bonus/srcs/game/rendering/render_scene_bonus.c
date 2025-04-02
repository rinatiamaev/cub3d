/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:06:19 by nlouis            #+#    #+#             */
/*   Updated: 2025/04/02 21:29:47 by nlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/**
 * @brief Initializes the framebuffer and z-buffer for rendering a new frame.
 *
 * This function allocates and sets up the rendering buffers used for the
 * current frame:
 *
 * - Allocates `z_buffer`, used for depth comparison during sprite rendering.
 * - Creates a new image using `mlx_new_image` and stores its metadata.
 * - Copies the pre-rendered background (`bg_img`) into the image buffer.
 *
 * This sets up a clean framebuffer with ceiling and floor colors already
 * drawn, ready for walls, entities, and UI to be rendered on top.
 *
 * @param game Pointer to the game state.
 * @param z_buffer Address of the z-buffer pointer to allocate and initialize.
 */
static void	setup_framebuffer(t_game *game, double **z_buffer)
{
	*z_buffer = x_calloc(game, WIN_W, sizeof(double));
	game->img.ptr = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp, &game->img.line_size, &game->img.endian);
	ft_memcpy(game->img.addr, game->bg_img.addr,
		WIN_W * WIN_H * (game->img.bpp / 8));
}

/**
 * @brief Renders the 3D world and in-world elements for the current frame.
 *
 * This function performs the core rendering of the scene:
 *
 * - Iterates over all screen columns to perform raycasting, storing wall
 *   distances in the z-buffer.
 * - Renders entities (NPCs and items) using the z-buffer for depth testing.
 * - Draws the minimap if enabled.
 *
 * The result is a full render of the world, ready to be composited with UI.
 *
 * @param game Pointer to the game state.
 * @param z_buffer Depth buffer used to sort sprites and avoid overdraw.
 */
static void	render_world(t_game *game, double *z_buffer)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
		raycast(game, &ray, &x, z_buffer);
	draw_entities(game, z_buffer);
	draw_minimap(game);
}

/**
 * @brief Renders the user interface elements on top of the scene.
 *
 * This function draws all 2D UI overlays, including:
 * - NPC dialogue boxes (if any NPC is speaking)
 * - Follow state messages
 * - Player inventory status (bucket/key)
 * - Splash animation (e.g., water effects)
 * - Temporary in-game messages
 *
 * These elements are drawn after the 3D world to ensure they appear on top.
 *
 * @param game Pointer to the game state (includes all UI state).
 * @param delta_time Time elapsed since last frame, used for animation timing.
 */
static void	render_ui(t_game *game, double delta_time)
{
	draw_npc_dialogue(game);
	draw_follow_state(game);
	draw_bucket_state(game);
	draw_splash(game, &game->player, delta_time);
	draw_temp_message(game);
}

/**
 * @brief Renders a complete frame, including the 2.5D world and UI.
 *
 * This is the main rendering function, called once per frame. It performs
 * the following steps in order:
 *
 * 1. Initializes the framebuffer and z-buffer with `setup_framebuffer`.
 * 2. Renders the 3D world (walls, sprites, minimap) via `render_world`.
 * 3. Pushes the final image to the window using `mlx_put_image_to_window`.
 * 4. Draws UI overlays like dialogue, messages, and effects via `render_ui`.
 * 5. Cleans up the framebuffer and z-buffer for the next frame.
 *
 * @param game Pointer to the game state (includes rendering and world data).
 * @param delta_time Time elapsed since last frame (used for animations).
 */
void	render_scene(t_game *game, double delta_time)
{
	double	*z_buffer;

	setup_framebuffer(game, &z_buffer);
	render_world(game, z_buffer);
	mlx_put_image_to_window(game->mlx, game->window->ptr, game->img.ptr, 0, 0);
	render_ui(game, delta_time);
	mlx_destroy_image(game->mlx, game->img.ptr);
	free(z_buffer);
}
