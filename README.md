# 3D Game Project

## Description
This project is part of the 42 Network curriculum, focusing on creating a simple 3D game using ray-casting techniques. The game engine is built from scratch using minimal external libraries, demonstrating core graphics programming concepts.

![Watch the demo video](https://github.com/aelbasri/MiniWolfenstein_3D/blob/main/utils/assets/demo.gif)

## Prerequisites
- GCC/Clang compiler
- Make
- MinilibX library (42's graphics library)
- Basic math library
- Operating System: Linux/macOS

## Installation
1. Clone the repository:
```bash
git clone git@github.com:aelbasri/MiniWolfenstein_3D.git
cd MiniWolfenstein_3D
```

2. Compile the project:
```bash
make
```

3. Run the game:
```bash
./cub3D utils/maps/map.cub
```

## Features
- 3D rendering using ray-casting
- Textured walls
- Player movement (WASD keys)
- Camera rotation (arrow keys)
- Collision detection
- Minimap display
- Basic game mechanics

## Controls
- `W` - Move forward
- `S` - Move backward
- `A` - Strafe left
- `D` - Strafe right
- `←` - Rotate camera left
- `→` - Rotate camera right
- `ESC` - Exit game
- `↑` - Open the door 
- `F` - Active the animation 

## Map Format
Maps should be formatted as follows:
```
1111111
1000001
1000001
100N001
1111111
```
- `1` represents walls
- `0` represents empty spaces
- `N/S/E/W` represents player starting position and orientation

## Error Handling
The program handles various error cases:
- Invalid map format
- Missing textures
- Memory allocation failures
- Invalid arguments

## Norminette
This project follows the 42 coding standard (Norm). All files pass Norminette checks.
