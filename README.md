# 🕹️ Cub3D

A 3D raycasting game written in C, inspired by Wolfenstein 3D. Built as a two-person project at Codam (42 Network), it renders a first-person view of a maze from a 2D map.

The project explores raycasting algorithms, graphics programming, texture mapping, and real-time player movement using MiniLibX.

This project was created with [Yaz](https://github.com/Y4ZK4Y).

## 🧩 Features
- **DDA raycasting:** Casts rays through the map grid to determine wall intersections and calculate wall distances.
- **Real-time rendering:** Projects walls into vertical screen slices, calculating their heights based on distance.
- **Directional wall textures:** Renders different textures depending on which side of a wall a ray hits.
- **Player movement:** Supports movement and camera rotation with keyboard input.
- **Collision detection:** Prevents the player from moving through walls.
- **Minimap:** Displays a top-down view of the maze and the player's position.
- **Map validation:** Parses .cub scene files and validates map structure, player position, textures, and floor and ceiling colours.
- **Resource management:** Handles texture loading, image buffers, and cleanup.

## 🔍 Technical Overview

**Raycasting:** Uses the DDA algorithm to traverse the 2D map grid and detect wall intersections. The calculated distance determines the projected wall height for each screen column.

**Texture rendering:** Calculates texture coordinates from wall intersection positions and orientations, then draws textured vertical wall slices into MLX42 image buffers.

**Map validation:** Parses scene files containing map data, texture paths, and floor and ceiling colours. Validates the map structure and checks that it is enclosed by walls before launching the game.

## 🚀 Build and Run
**Prerequisites:** A compatible environment with the required MiniLibX/MLX42 dependencies and build tools.

Build the project:

```bash
make
```

Run the game with a .cub map file:
```bash
./cub3D mapgs/good/catacombs.cub
```

Replace the map path with another valid .cub file from the repository.

## 🎮 Controls

| Key | Action |
|---|---|
| W / A / S / D | Move through the maze |
| Left / Right arrows | Rotate the camera |
| ESC | Exit the game |

## 🛠️ Technologies
- C
- MiniLibX / MLX42
- DDA raycasting
- Mathematics and vector calculations
- Graphics and texture rendering
- Make
