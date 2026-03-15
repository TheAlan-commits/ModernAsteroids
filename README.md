# Modern Asteroids

A modern recreation of the classic **Asteroids** arcade game built in **C++** using **SFML**.
This project is being developed collaboratively for a Computer Science course at **East Carolina University**.

## Team Members

* Alan Escamilla
* Eri Adebanji
* Terrance Whitley

## Project Description

Modern Asteroids is a modernized version of the classic Asteroids game where the player pilots a spaceship and must destroy incoming asteroids while avoiding collisions. 
The project focuses on implementing core game development concepts such as a game loop, collision detection, object-oriented design, and real-time rendering using SFML.

## Technologies

* **Language:** C++
* **Graphics Library:** SFML
* **Build System:** CMake
* **Development Environment:** Visual Studio Code
* **Version Control:** Git & GitHub

## Project Structure

```
Modern-Asteroids/
│
├── src/        # C++ source files
├── include/    # Header files
├── assets/     # Game graphics, textures, and audio
├── docs/       # Planning documents and notes
├── build/      # Compiled files (generated when building)
│
├── CMakeLists.txt
└── README.md
```

## Setup Instructions

Before building the project, install **CMake** and **SFML**.

### macOS (using Homebrew)

Install Homebrew if needed:

https://brew.sh

Then install dependencies:

```
brew install cmake
brew install sfml
```

### Windows

1. Install **CMake**
   https://cmake.org/download/

2. Download **SFML**
   https://www.sfml-dev.org/download.php

3. Extract the SFML folder and follow the setup instructions for your compiler (Visual Studio or MinGW).

Note: Using **CMake with Visual Studio** is recommended for Windows users.

## Clone the Repository

```
git clone https://github.com/TheAlan-commits/ModernAsteriods.git
cd ModernAsteriods
```

## Build the Project

```
mkdir build
cd build
cmake ..
cmake --build .
```

## Run the Program

After building successfully:

```
./bin/main
```

This will open the initial SFML window used to confirm the project is set up correctly.

## Development Goals

Planned features include:

* Player spaceship movement
* Asteroid spawning and movement
* Bullet shooting mechanics
* Collision detection
* Score tracking
* Sound effects and visual improvements

## Notes

This project is currently in the early development stage. 
The main focus is establishing the development environment and project structure before implementing gameplay features.
