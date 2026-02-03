# cub3D - Raycasting Game Engine

<div align="center">
  <img src="https://img.shields.io/badge/42-Project-blue" alt="42 Project">
  <img src="https://img.shields.io/badge/Language-C-brightgreen" alt="Language">
  <img src="https://img.shields.io/badge/Graphics-MLX-orange" alt="MLX">
</div>

## 📖 Table of Contents
- [About](#about)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Map Configuration](#map-configuration)
- [Controls](#controls)
- [Project Structure](#project-structure)
- [Bonus Features](#bonus-features)
- [Authors](#authors)

## 🎮 About

**cub3D** is a 3D game engine inspired by the legendary Wolfenstein 3D, the first-ever FPS. This project demonstrates raycasting techniques to create a 3D graphical representation from a 2D map. Built using the MiniLibX graphics library, it provides an immersive first-person perspective game experience.

The project is part of the 1337 school curriculum and teaches fundamental concepts of:
- Raycasting algorithms
- 3D projection and perspective
- Game physics and collision detection
- Event handling and user input
- Graphics programming with MLX

## ✨ Features

### Mandatory Features
- **3D Raycasting Engine**: Real-time 3D rendering using raycasting techniques
- **First-Person Navigation**: Move through the maze with smooth player controls
- **Textured Walls**: Different textures for North, South, East, and West walls
- **Customizable Colors**: Configurable floor and ceiling colors
- **Collision Detection**: Players cannot walk through walls
- **Window Management**: Clean exit on ESC key or window close button
- **Map Parsing**: Support for `.cub` map files with validation

### Bonus Features
- **Minimap**: Real-time 2D minimap showing player position and orientation
- **Animated Sprites**: Support for sprite animations (gun animation)
- **Doors**: Interactive door system (open/close with spacebar)
- **Mouse Control**: Look around using mouse movement
- **Enhanced Graphics**: Additional visual effects and textures
- **Multiple Maps**: Various pre-configured maps to explore

## 🔧 Prerequisites

Before installing cub3D, make sure you have the following dependencies:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev

# Fedora
sudo dnf install gcc make xorg-x11-server-Xorg libXext-devel libbsd-devel

# Arch Linux
sudo pacman -S gcc make xorg-server libxext libbsd
```

### MiniLibX Library
The project uses MiniLibX for graphics rendering. Clone it:
```bash
git clone https://github.com/42Paris/minilibx-linux.git mlx
cd mlx
make
```

## 📥 Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/Youness-Tr/cub3D.git
   cd cub3D
   ```

2. **Compile the mandatory version**
   ```bash
   make
   ```

3. **Compile the bonus version** (with additional features)
   ```bash
   make bonus
   ```

4. **Clean object files**
   ```bash
   make clean    # Remove .o files
   make fclean   # Remove .o files and executables
   make re       # Recompile from scratch
   ```

## 🚀 Usage

### Running the Mandatory Version
```bash
./cub3D Assets/maps/map_00.cub
```

### Running the Bonus Version
```bash
./cub3D_bonus Assets/maps/map_bonus01.cub
```

### Available Maps
- `Assets/maps/map_00.cub` - Basic map
- `Assets/maps/map_01.cub` - Medium complexity
- `Assets/maps/map_02.cub` - Advanced layout
- `Assets/maps/map_bonus01.cub` - Bonus features map
- `Assets/maps/map_bonus02.cub` - Extended bonus map
- `Assets/maps/subject.cub` - Subject example map

## 🗺️ Map Configuration

### Map File Format (.cub)

A valid `.cub` file contains:

1. **Texture Paths**: Define wall textures for each direction
   ```
   NO ./Assets/Textures/eagle_wolf.xpm       # North wall texture
   SO ./Assets/Textures/bluestone_wolf.xpm   # South wall texture
   WE ./Assets/Textures/mossy_wolf.xpm       # West wall texture
   EA ./Assets/Textures/greystone_wolf.xpm   # East wall texture
   ```

2. **Colors**: RGB values for floor and ceiling
   ```
   F 56,56,56      # Floor color (R,G,B)
   C 112,112,11    # Ceiling color (R,G,B)
   ```

3. **Map Layout**: 2D representation using specific characters
   ```
   111111
   110001
   10N001    # N = Player starting position facing North
   110011
    1001
    1001
   110011
   100001
   111111
   ```

### Map Characters

| Character | Description |
|-----------|-------------|
| `0` | Empty space (walkable) |
| `1` | Wall |
| `N` | Player start position (facing North) |
| `S` | Player start position (facing South) |
| `E` | Player start position (facing East) |
| `W` | Player start position (facing West) |
| `D` | Door (bonus only) |
| `space` | Outside map (treated as void) |

### Map Rules
- Map must be surrounded by walls (1s)
- Must contain exactly one player start position (N/S/E/W)
- All textures must be valid XPM files
- RGB values must be in range [0-255]
- Map must be rectangular (can have spaces for irregular shapes)

### Example Map
```
NO ./Assets/Textures/wall_1.xpm
SO ./Assets/Textures/wall_2.xpm
WE ./Assets/Textures/wall_3.xpm
EA ./Assets/Textures/wall_4.xpm

F 100,100,100
C 135,206,235

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

## 🎮 Controls

### Mandatory Controls
| Key | Action |
|-----|--------|
| `W` | Move forward |
| `A` | Move left (strafe) |
| `S` | Move backward |
| `D` | Move right (strafe) |
| `←` (Left Arrow) | Rotate camera left |
| `→` (Right Arrow) | Rotate camera right |
| `ESC` | Exit game |

### Bonus Controls (Additional)
| Key/Input | Action |
|-----------|--------|
| `SPACE` | Open/Close door (when near) |
| `Left Mouse Button` | Shoot (trigger gun animation) |
| `Mouse Movement` | Look around (rotate camera) |

## 📁 Project Structure

```
cub3D/
├── Makefile                    # Build configuration
├── README.md                   # This file
├── Assets/                     # Game resources
│   ├── door/                   # Door sprites (bonus)
│   ├── gun/                    # Gun animation frames (bonus)
│   ├── maps/                   # Map configurations (.cub files)
│   ├── sprites/                # Additional sprites
│   └── Textures/               # Wall textures (.xpm files)
├── Gnl/                        # Get Next Line (file reading)
│   ├── get_next_line.c
│   ├── get_next_line.h
│   └── gnl_utils.c
├── mandatory/                  # Mandatory part implementation
│   ├── main_cub.c              # Entry point
│   ├── Header/                 # Header files
│   │   └── cub3d.h
│   ├── Glogic/                 # Game logic
│   │   ├── playerMoves.c       # Player movement
│   │   └── Wall_Intersection.c # Collision detection
│   ├── Init/                   # Initialization
│   │   ├── init.c              # Engine initialization
│   │   └── init1.c
│   ├── Leaks/                  # Memory management
│   │   ├── free_all.c          # Cleanup functions
│   │   └── garbedge.c          # Garbage collection
│   ├── Parsing/                # Map parsing
│   │   ├── parser.c            # Main parser
│   │   ├── tool.c
│   │   ├── utils.c
│   │   ├── utils2.c
│   │   └── utils3.c
│   ├── RayCasting/             # Raycasting engine
│   │   ├── raycaster.c         # Main raycasting algorithm
│   │   └── raytools.c          # Ray utilities
│   ├── Rendring/               # Rendering engine
│   │   ├── render3D.c          # 3D rendering
│   │   └── render_utils.c
│   └── Utils/                  # Utility functions
│       ├── err.c               # Error handling
│       ├── split.c             # String splitting
│       ├── strdup.c
│       ├── substr.c
│       └── utils1.c
└── bonus/                      # Bonus part (same structure + extras)
    ├── main_cub_bonus.c
    ├── Header/
    │   └── cub3d_bonus.h
    ├── Glogic/
    │   ├── elements_bonus.c    # Additional game elements
    │   ├── events_bonus.c      # Event handling
    │   ├── playerMoves_bonus.c
    │   └── Wall_Intersection_bonus.c
    ├── Init/
    │   ├── init_bonus.c
    │   ├── init_textures.c     # Texture loading
    │   ├── init_utils_bonus.c
    │   └── init1_bonus.c
    ├── Rendring/
    │   ├── render2d_bonus.c    # Minimap rendering
    │   ├── render3D_bonus.c
    │   └── render_utils_bonus.c
    └── [Other directories similar to mandatory]
```

## 🎁 Bonus Features

The bonus version includes several enhancements:

### 1. Minimap
- Real-time 2D overhead view in the corner
- Shows player position and orientation
- Displays walls, empty spaces, and doors
- Scale: configurable via `MINI_MAP` and `MINI_TILE` defines

### 2. Interactive Doors
- Open/close doors using SPACEBAR when near
- Visual feedback when door is interactive
- Distance-based interaction (`DOOR_OPEN_DISTANCE`)
- Smooth door animations

### 3. Animated Gun/Weapon
- Gun sprite at bottom of screen
- Fire animation on left mouse click
- Multiple animation frames for realism
- Configurable via `MAX_GUN` frames

### 4. Mouse Look
- Rotate camera using mouse movement
- Smooth rotation with configurable sensitivity
- Left/right mouse buttons for actions

### 5. Enhanced Visuals
- More detailed textures
- Better color management
- Optimized rendering with texture scaling (`ZOOM_TEXTURE`)

## 🔍 Technical Details

### Raycasting Algorithm
The engine uses DDA (Digital Differential Analysis) raycasting:
1. Cast rays for each column of the screen (based on FOV)
2. Calculate ray direction and position
3. Perform DDA to find wall intersections
4. Calculate perpendicular distance to avoid fish-eye effect
5. Calculate wall height based on distance
6. Texture mapping for each vertical strip

### Window Specifications
**Mandatory:**
- Resolution: 1920x1080
- Tile Size: 64 pixels
- FOV: 60 degrees

**Bonus:**
- Resolution: 1000x920
- Tile Size: 32 pixels
- FOV: 60 degrees
- Minimap scale: 0.25x

## 🐛 Error Handling

The program validates:
- ✅ Correct number of arguments
- ✅ Valid `.cub` file extension
- ✅ File accessibility and readability
- ✅ Valid texture paths and XPM files
- ✅ Valid RGB color values (0-255)
- ✅ Proper map format and closure
- ✅ Single player start position
- ✅ No invalid characters in map

### Common Errors
```bash
# Wrong usage
./cub3D                           # Missing map file
./cub3D map.txt                   # Wrong extension
./cub3D map1.cub map2.cub         # Too many arguments

# Correct usage
./cub3D Assets/maps/map_00.cub    # ✓
```

## 🔧 Compilation Flags

```makefile
CC = cc
CFLAGS = -Wall -Wextra -Werror    # Standard 42 flags
MLX_FLAGS = -Lmlx -lmlx_Linux -lXext -lX11 -lm
```

For debugging, uncomment in Makefile:
```makefile
MLX_FLAGS += -fsanitize=address -g3
```

## 💡 Tips

1. **Performance**: Keep window size reasonable for smooth FPS
2. **Map Design**: Ensure maps are closed and valid to prevent crashes
3. **Textures**: Use small XPM files (64x64 or 128x128) for better performance
4. **Testing**: Try different map configurations to test edge cases
5. **Debugging**: Use the address sanitizer flag for memory leak detection

## 🎓 Learning Resources

- [Raycasting Tutorial by Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)
- [Game Engine Black Book: Wolfenstein 3D](https://fabiensanglard.net/gebbwolf3d/)
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)

## 👥 Authors

- **ytarhoua** - [GitHub](https://github.com/Youness-Tr)
- **ajabri** - Collaborator

## 📄 License

This project is part of the 1337 school 42 network curriculum. Feel free to use it for educational purposes.

---

<div align="center">
  <sub>Built with ❤️ for 1337 School</sub>
</div>
