# Hypotrochoid Visualizer

![C++](https://img.shields.io/badge/C%2B%2B-11-00599C?logo=c%2B%2B&logoColor=white)
![raylib](https://img.shields.io/badge/built%20with-raylib-black)
<!-- Optional license badge, once you add a LICENSE file:
![License](https://img.shields.io/github/license/YOUR-USERNAME/YOUR-REPO) -->

An interactive C++ program that animates a **hypotrochoid**: the curve traced by a pen attached to a small circle as it rolls around the inside of a larger one. The program draws both circles, the pen arm, and the trail the pen leaves behind, and it cycles through a set of presets that produce stars with 4 to 12 points.

<img width="780" height="732" alt="Hypotrochoid" src="https://github.com/user-attachments/assets/5674fca2-fcfc-43d6-aa29-62e4ff15c814" />


## Table of Contents

- [Features](#features)
- [Anatomy of the Drawing](#anatomy-of-the-drawing)
- [The Math](#the-math)
- [Presets](#presets)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Configuration](#configuration)
- [Choosing Your Own Values](#choosing-your-own-values)
- [How It Works](#how-it-works)
- [Troubleshooting](#troubleshooting)
- [Project Structure](#project-structure)
- [Feedback](#feedback)
- [License](#license)
- [Acknowledgments](#acknowledgments)

## Features

- Real-time animation of the rolling circle, pen arm, and pen trail
- Computed directly from the hypotrochoid parametric equations
- Eight built-in presets that cycle with a single key press
- Graph-style coordinates (y points up), converted to screen pixels in a single place
- Small and dependency-light: one source file and raylib

## Anatomy of the Drawing

<img width="232" height="188" alt="image" src="https://github.com/user-attachments/assets/29399c57-8c0e-47c3-8641-6c1f7782d38a" />


| Element | Color | Meaning |
| --- | --- | --- |
| Big circle | Blue | Fixed circle of radius `R`, centered on the origin |
| Rolling circle | Black | Circle of radius `r` that rolls along the inside of the big circle |
| Pen arm | Black line | Connects the rolling circle's center to the pen |
| Pen | Red dot | The drawing point, a distance `d` from the rolling circle's center |
| Trail | Red line | The path the pen has traced so far |

## The Math

A hypotrochoid is described by two parametric equations:

<img width="338" height="85" alt="image" src="https://github.com/user-attachments/assets/b35814a2-0f86-4452-9525-9c7e7ff80fd1" />

| Symbol | Meaning |
| --- | --- |
| `R` | Radius of the big (fixed) circle |
| `r` | Radius of the small (rolling) circle |
| `d` | Distance from the rolling circle's center to the pen |
| `θ` | Angle of the rolling circle's center around the big circle, in radians |

The first term of each equation is the position of the rolling circle's center, which travels on a circle of radius `R - r`. The second term is the pen arm of length `d`, which spins at `(R - r) / r` times the speed of `θ`.

### Effect of the pen distance `d`

| `d` compared to `r` | Pen position | Result |
| --- | --- | --- |
| `d < r` | Inside the rolling circle | Rounded shape, no loops |
| `d = r` | On the rim of the rolling circle | Sharp points that touch the big circle |
| `d > r` | Outside the rolling circle | Points that extend past the big circle, with a loop at each tip |

## Presets

The program ships with eight presets. Each one is a star with a different number of points.

| # | `R` | `r` | `d` | Points | Shape | Preview |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | 4 | 3 | 5 | 4 | Rounded square with curved-in sides | `[IMAGE 5]` |
| 2 | 5 | 3 | 5 | 5 | Five-pointed star | `[IMAGE 6]` |
| 3 | 7 | 4 | 6 | 7 | Seven-pointed star | `[IMAGE 7]` |
| 4 | 8 | 5 | 7 | 8 | Eight-pointed star | `[IMAGE 8]` |
| 5 | 9 | 5 | 7 | 9 | Nine-pointed star | `[IMAGE 9]` |
| 6 | 10 | 7 | 9 | 10 | Ten-pointed star | `[IMAGE 10]` |
| 7 | 11 | 6 | 8 | 11 | Eleven-pointed star | `[IMAGE 11]` |
| 8 | 12 | 7 | 9 | 12 | Twelve-pointed star | `[IMAGE 12]` |

## Getting Started

### Requirements

- A C++ compiler with C++11 support (g++, clang, or MSVC)
- [raylib](https://github.com/raysan5/raylib) installed (see the raylib repository for installation instructions)

### Build

Replace `main.cpp` with the name of your source file.

**Linux**

```bash
g++ main.cpp -o hypotrochoid -std=c++11 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

**macOS**

```bash
g++ main.cpp -o hypotrochoid -std=c++11 -lraylib -framework IOKit -framework Cocoa -framework OpenGL
```

**Windows (MinGW)**

```bash
g++ main.cpp -o hypotrochoid.exe -std=c++11 -lraylib -lopengl32 -lgdi32 -lwinmm
```

**Windows (Visual Studio):** create a project from the raylib Visual Studio template and add `main.cpp` to it.

### Run

```bash
./hypotrochoid
```

## Usage

| Key | Action |
| --- | --- |
| `Space` | Switch to the next preset and restart the drawing |
| `Esc` | Quit |

After the last preset, `Space` returns to the first one.

## Configuration

Everything you can change is at the top of `main()`.

| Setting | Description |
| --- | --- |
| `Rvalues` | List of big circle radii, one per preset |
| `rvalues` | List of rolling circle radii, one per preset |
| `dvalues` | List of pen distances, one per preset |
| `speed` | How much `θ` grows each frame. Smaller is smoother but slower |
| `unit` | Pixels per graph unit. Lower it if a drawing goes off screen |

The three lists are matched by position: the first entry of each list describes preset 1, the second entry describes preset 2, and so on. To add a preset, add one value to **each** of the three lists.

## Choosing Your Own Values

- **Number of points:** `R / gcd(R, r)`, where `gcd` is the greatest common divisor. Use whole numbers for `R` and `r`.
- **Stars with crossing lines:** choose `r` so that it shares no factor with `R` and is neither `1` nor `R - 1`. Every number of points from 5 upward has a valid `r`. The exceptions are 3, 4, and 6 points, which can only produce rounded polygons or separate loops.
- **A good starting recipe:** set `R` to the number of points you want, set `r` to a value a little over half of `R` that shares no factor with `R`, and set `d = r + 2`.
- **Sharper or rounder points:** make `d` closer to `r` for sharper points, or larger for fatter points.

## How It Works

Each frame the program:

1. Computes the rolling circle's center `C` from `θ`, at distance `k = R - r` from the origin.
2. Computes the pen position from the parametric equations.
3. Adds the pen position to the trail and increases `θ` by `speed`.
4. Draws the trail as short line segments, then the two circles, the pen arm, and the pen.

| Variable | Meaning |
| --- | --- |
| `k` | `R - r`, the distance from the origin to the rolling circle's center |
| `theta` | The angle `θ`, which drives the whole animation |
| `C` | Screen position of the rolling circle's center |
| `pen` | Screen position of the pen |
| `trail` | List of every pen position so far |
| `screen` | A lambda that converts graph coordinates to pixels |

The `screen` lambda scales by `unit`, shifts the origin to the middle of the window, and flips the vertical axis so that y points up like on a normal graph.

The curve closes after `θ = 2π · r` for whole-number `R` and `r`, and the program stops adding points at that moment.

## Troubleshooting

| Problem | Fix |
| --- | --- |
| The curve looks jagged or the points are cut off | Lower `speed` (for example `0.03f`) |
| The drawing goes off the screen | Lower `unit` |
| The shape has fewer points than expected | `R` and `r` share a factor. Pick an `r` with no factor in common with `R` |
| Drawing is too slow | Raise `speed` a little, but not much past `0.05f` |

## Project Structure

```
.
├── main.cpp
├── README.md
├── LICENSE
└── docs/
    └── images/
        ├── demo.gif
        ├── anatomy.png
        ├── math-diagram.png
        ├── pen-distance.png
        └── preset-*.png
```

## Feedback

Issues and suggestions are welcome.

## Acknowledgments

- [raylib](https://github.com/raysan5/raylib), the library used for windowing and drawing
