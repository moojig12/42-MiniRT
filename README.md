A ray tracing project from the 42 Core Curriculum (Circle 4), built with C and MiniLibX.

This repository contains two builds:
- `miniRT`: standard renderer
- `miniRT_threaded`: threaded/bonus renderer

## Features

- Ray tracing with recursive light bounces
- Scene parsing from `.rt` files
- Primitive support: sphere, plane, cylinder
- Camera and light support
- Interactive object selection, movement, and rotation
- Toggle between LOW and HIGH render modes at runtime
- Bonus/threaded build with optional material + emission settings

## Prerequisites

Linux/X11 environment with development headers:

- `xorg`
- `libx11-dev`
- `libxext-dev`
- `libxrandr-dev`
- `libxi-dev`
- `libxpm-dev`
- `libxcb1-dev`
- `libx11-xcb-dev`
- `libbsd-dev`
- `make`, `cc`, `git`

Example install (Debian/Ubuntu):

```bash
sudo apt-get update
sudo apt-get install -y xorg libxcb1-dev libx11-xcb-dev libx11-dev \
  libxext-dev libxrandr-dev libxi-dev libxpm-dev libbsd-dev make gcc git
```

## Build

From the repository root:

```bash
make
```

Build threaded/bonus target:

```bash
make thread
```

Clean targets:

```bash
make clean
make fclean
make re
```

## Run

```bash
./miniRT <scene.rt>
# or
./miniRT_threaded <scene.rt>
```

Example:

```bash
./miniRT scenes/eval.rt
```

## Scene format

### Mandatory identifiers

- `A` ambient light: `A <ratio 0.0-1.0> <R,G,B>`
- `C` camera: `C <x,y,z> <nx,ny,nz> <fov 0-180>`
- `L` light: `L <x,y,z> <brightness 0.0-1.0> <R,G,B>`
- `sp` sphere: `sp <x,y,z> <diameter> <R,G,B>`
- `pl` plane: `pl <x,y,z> <nx,ny,nz> <R,G,B>`
- `cy` cylinder: `cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>`

### Bonus/threaded extras

- `E` emission config: `E <sample_size> <max_depth>`
- Optional material token on objects:
  - sphere/plane: append `<material>`
  - cylinder: append `<material>` after color
- Recognized material strings: `metal`, `glass`, `plastic` (others fall back to default)

## Runtime controls

### Selection

- `1`: select camera
- `2`: select light (cycle)
- `3`: select sphere (cycle)
- `4`: select cylinder (cycle)
- `5`: select plane (cycle)

### Movement

- `W/A/S/D`: move selected object
- `Space`: move up
- `Left Ctrl`: move down

### Rotation

- `Q` / `E`: rotate camera view left/right
- `I/K`: rotate selected object around X axis
- `J/L`: rotate selected object around Y axis
- `U/O`: rotate selected object around Z axis

### Misc

- `R`: toggle render quality (LOW/HIGH, where LOW is faster preview and HIGH is higher quality)
- `P`: print selected object transform to stdout
- `G`: toggle emissive flag on selected object
- `Esc`: close window

## Project layout

- `/srcs` core rendering, parsing, controls, math
- `/srcs/parser` mandatory parser
- `/srcs/parser_bonus` threaded/bonus parser
- `/incl` headers + bundled `libft`, `get_next_line`, `minilibx-linux`
- `/scenes` sample `.rt` scenes

## Notes

- The Makefile currently compiles with `-fsanitize=address -g -O3` and enables AddressSanitizer by default.
- This is useful for debugging but slower for normal runs; remove `-fsanitize=address` from `CFLAGS` in the Makefile for non-sanitized builds.
- `make` will fetch/build MiniLibX if needed.
- Program expects scene files with `.rt` extension.

## Authors

- fjoestin
- nmandakh
