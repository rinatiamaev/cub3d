# Raycasting
Raycasting is the core technique behind rendering the 3D-like view in Cub3D. At its heart, raycasting converts a 2D map (usually a grid where each cell represents a wall or empty space) into a pseudo-3D scene by “casting” rays from the player's viewpoint and determining where they hit a wall. Here’s a breakdown of the key concepts:

**1. Basic concept**
- **2D to 3D Projection:**
Imagine standing in a maze and looking straight ahead. Instead of drawing the entire maze at once, raycasting sends out a ray for every vertical slice of your screen. Each ray travels until it hits a wall in the 2D map.

- **Distance Calculation:**
The distance from the player to the wall along each ray determines how tall that wall slice appears on your screen. Walls that are closer appear taller, while walls farther away appear shorter.