# Modern Asteroids

Modern Asteroids is a modern recreation of the classic **Asteroids arcade game**, built in **C++ using SFML**.

This project is being developed collaboratively for a **Computer Science course at East Carolina University**.

The goal of the project is to implement core game development concepts such as a game loop, collision detection, object-oriented programming, and real-time rendering using SFML.

---

# Team Members

* Alan Escamilla
* Eri Adebanji
* Terrance Whitley

---

# Technologies

* **Language:** C++
* **Graphics Library:** SFML
* **Build System:** CMake
* **Development Environment:** Visual Studio Code
* **Version Control:** Git & GitHub

---

# Project Structure

```
ModernAsteroids/
│
├── src/        # C++ source files
├── include/    # Header files
├── assets/     # Game graphics, textures, and audio
├── docs/       # Planning documents and notes
├── build/      # Compiled files (generated during build)
│
├── CMakeLists.txt
└── README.md
```

---

# Setup Instructions

Before building the project, install the required dependencies.

## macOS

Install **Homebrew** if it is not already installed:

https://brew.sh

Then install the required packages:

```bash
brew install cmake
brew install sfml
```

---

## Windows

1. Install **CMake**

https://cmake.org/download/

2. Download **SFML**

https://www.sfml-dev.org/download.php

3. Extract the SFML folder and follow the setup instructions for your compiler (Visual Studio or MinGW).

Using **CMake with Visual Studio** is recommended for Windows users.

---

# Clone the Repository

```bash
git clone https://github.com/TheAlan-commits/ModernAsteroids.git
cd ModernAsteroids
```

---

# Build the Project

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

# Run the Program

After building successfully:

```bash
./bin/main
```

This will open the initial SFML window used to confirm that the development environment is working correctly.

---

# Development Workflow

Since multiple team members will be working on the project, please follow this workflow.

### 1. Pull the latest changes

```bash
git pull origin main
```

### 2. Create a feature branch

```bash
git checkout -b feature-name
```

Example:

```
git checkout -b spaceship-movement
git checkout -b asteroid-system
git checkout -b collision-detection
```

### 3. Commit your changes

```bash
git add .
git commit -m "Add player spaceship movement"
```

### 4. Push your branch

```bash
git push origin feature-name
```

### 5. Create a Pull Request

Open a **Pull Request on GitHub** so the team can review the changes before merging them into `main`.

---

# Development Guidelines

* Do **not commit directly to the `main` branch**
* Use **clear commit messages**
* Work in **feature branches**
* Pull the latest changes before starting work
* Keep code organized and documented

---

# Sprint Plan

Development will be organized into **two-week sprints**.

## Sprint 1 (Weeks 1–2)

Project setup and core player controls

Goals:

* Project setup and environment configuration
* Basic spaceship movement
* Initial SFML window and game loop

---

## Sprint 2 (Weeks 3–4)

Asteroid system

Goals:

* Asteroid spawning
* Asteroid movement

---

## Sprint 3 (Weeks 5–6)

Combat and physics

Goals:

* Shooting mechanics
* Collision detection

---

## Sprint 4 (Weeks 7–8)

Gameplay systems

Goals:

* Score system
* Game over system

---

## Final Weeks

Final polishing and preparation

Goals:

* Debugging
* Gameplay improvements
* Final presentation/demo

---

# Notes

This project is currently in the **early development stage**. The immediate goal is ensuring that all team members can successfully build and run the project before implementing gameplay features.
