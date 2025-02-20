<h2 align="center">
	REPOSITORY STATS
</h2>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/gecarval/Particle-Life?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/gecarval/Particle-Life?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/gecarval/Particle-Life?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/gecarval/Particle-Life?color=green" />
</p>
This project is written in C using the MiniLibX as the API.

# LifeSim
This program simulates gravitational attraction with defined rules, such as the range of the gravitional attraction and the strenght of this force, being it negative or posivitive, in other words an attractive force or a repulsive force defined by a diametre.

The gimic is that there are thousands of this particles and each one of those will behave diferently (attration or repulsion) acording to his colours, which can be a range between 1 to 6 different ones.

![Example](https://github.com/user-attachments/assets/f0502d2f-d8a9-4c3a-bf86-5de2695eb275)

> [!Note]
> The red line is the range of the repulsive force, and the green one is the attractive force.

The interesting thing is the type of behavior and complex structures that can form from such simple rules that are defined by the programmer, but the result is unprecdicteble from the user stand point, which create patterns from an emergent behavior as the Conway's game of life.

# Demo

![3 creatures ecosystem](https://github.com/user-attachments/assets/522d1c4e-945f-4066-b734-c82227a53296)
> [!Note]
> Look at how they move as they have they on life.

![Agressive creature](https://github.com/user-attachments/assets/0eb542a1-0f8f-4163-aedd-75fec1f3b9d8)
> [!Note]
> Even agressive behaviors can spawn.

![Giant ecosystem](https://github.com/user-attachments/assets/c920310e-171d-4b4d-aa3b-f4072a2ab8dd)
> [!Note]
> In the end this is how the emulation is presented.

# Installation
The project uses the [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) using the X11 Window system in the Linux Operating System, after the instalation of all dependencies you should do as required:

- Clone the repository;
``` sh
git clone https://github.com/gecarval/Particle-Life.git
```
- Move to the folder;
``` sh
cd Particle-Life
```
- Compile the project;
``` sh
make
```
- execute the program;
``` sh
./render [Put Window Width] [Put Window Height]
```
- execution examples:
``` sh
./render 800 600
```
``` sh
./render 1600 900
```
``` sh
./render 1900 1000
```
## Controls
|BUTTON|ACTION|
|---|---|
|`R`| Random Rules|
|`T`| Reset Positions|
|`Y`| Show Quadtree|
|`LMB`| activate brush|
|`Esc`| Exit|
|`[`| increase speed|
|`]`| decrease speed|
|`1`| on/off Particle life|
|`Space`| clear screen|
