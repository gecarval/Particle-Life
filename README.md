<div align="center">

# Particle Life

### Six colours, one table of likes and dislikes, and 2 000 particles that start to look alive.

![3 creatures ecosystem](https://github.com/user-attachments/assets/522d1c4e-945f-4066-b734-c82227a53296)

<p>
<img alt="C" src="https://img.shields.io/badge/C-A8B9CC?logo=c&logoColor=black" />
<img alt="MiniLibX" src="https://img.shields.io/badge/MiniLibX-X11-555" />
<img alt="pthreads" src="https://img.shields.io/badge/pthreads-20%20threads-orange" />
<img alt="License" src="https://img.shields.io/github/license/gecarval/Particle-Life?color=green" />
<img alt="Last commit" src="https://img.shields.io/github/last-commit/gecarval/Particle-Life?color=green" />
</p>

[Build](#build-and-run) · [The rules](#the-rules) · [Gallery](#gallery) · [How it works](#how-it-works) · [Controls](#controls)

</div>

---

Every particle has a colour. Every colour has an opinion about every other colour: red might chase green, green might flee from red, blue might ignore both. That is the whole program. Nothing in the code says "cell", "worm" or "predator", yet press `R` a few times and you will find all three.

## Build and run

You need a C compiler, `make`, and the X11 development headers (`libx11` and `libxext`; on Debian/Ubuntu, `libx11-dev libxext-dev`). MiniLibX and libft are bundled.

```bash
git clone https://github.com/gecarval/Particle-Life.git
cd Particle-Life
make
./render              # 1200 × 800 window
./render 1600 900     # or choose the size
```

Press `R` until you get a world you like. Each new rule set is printed in the terminal as a table.

## The rules

Each pair of colours *(A, B)* gets three random numbers when the world starts, and new ones every time you press `R`:

| Table | Range | Meaning |
|---|---|---|
| **Strength** | up to ± 1.5 | how strongly A is pulled toward B (positive) or pushed away (negative) |
| **Reach** | 30 – 60 px | how far away A can feel B |
| **Personal space** | 6 – 12 px | inside this distance A is always pushed away from B, whatever the strength |

The tables are **not symmetric**: A's feelings about B are drawn separately from B's feelings about A. When red likes green but green dislikes red, red follows green and green runs, and you get chases, orbits and "creatures" that swim across the screen. Symmetric rules tend to settle into still clumps instead.

![Interaction ranges](https://github.com/user-attachments/assets/f0502d2f-d8a9-4c3a-bf86-5de2695eb275)

<sub>Red: the personal-space radius where particles push apart. Green: the reach of attraction.</sub>

## Gallery

| | |
|:---:|:---:|
| ![Aggressive creature](https://github.com/user-attachments/assets/0eb542a1-0f8f-4163-aedd-75fec1f3b9d8) | ![Giant ecosystem](https://github.com/user-attachments/assets/c920310e-171d-4b4d-aa3b-f4072a2ab8dd) |
| A rule set that produces a predator | A full screen of 2 000 particles |

## How it works

Each frame, for every pair of particles closer than the reach in the tables:

```
force = strength[A][B] × mass / clamp(distance², 100, 1000)
```

That is gravity with a sign and a colour. The `clamp` keeps the force from exploding when two particles nearly touch, and from vanishing at the edge of the reach. On top of that:

- **Personal space** adds a repulsion with a constant of 3, against 1 for attraction.
- **Collisions** are elastic. Overlapping particles are pushed apart and swap momentum, resolved in 4 passes per frame.
- **Friction** removes 1 % of the velocity every frame, so the system does not heat up forever.
- **The world wraps around**: a particle leaving on the right comes back on the left, and forces are measured across the edges too, so there are no walls to pile up against.

### Performance

- The force pass compares every pair of particles, so it costs O(n²). It is split across **20 POSIX threads**, each handling a slice of the particles, with a mutex per particle.
- Collisions use a **quadtree** (4 particles per node, at most 8 levels), so a particle only checks the ones near it. Press `Y` to see the tree.

```
main.c, calls.c, reads.c, tools.c   window, setup, input, rule tables
lifesim.c                           forces, collisions, friction, threads
quadtree.c                          quadtree build and queries
vector_calc.c                       2D vectors, wrap-around
cubix/                              Bresenham line drawing
includes/renderer.h                 constants (threads, colours, quadtree)
```

## Controls

| Key | Action | Key | Action |
|---|---|---|---|
| `R` | new random rules | `LMB` | start / stop painting new particles |
| `T` | scatter all particles again | `[` / `]` | faster / slower |
| `Y` | show the quadtree | `1` | pause / resume |
| `Space` | clear the screen | `Esc` | quit |

## Further reading

- Jeffrey Ventrella, [*Clusters*](https://www.ventrella.com/Clusters/), where the idea of particle life comes from
- Tom Mohr, [*Particle Life*](https://particle-life.com/)
- Daniel Shiffman, [*The Nature of Code*: Forces](https://natureofcode.com/forces/)

---

<div align="center">

Released under the [BSD 2-Clause License](./LICENSE) · Made by [Gerson Carvalho](https://github.com/gecarval) at 42

</div>
