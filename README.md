# Adventure Game

## Overview

**Adventure Game** is an interactive, graphics-based application designed to provide an engaging gaming experience while demonstrating strong software engineering principles. Built using **Qt**, a cross-platform application development framework, the game integrates object-oriented programming, pathfinding algorithms, and modern GUI design.

This project showcases my ability to design and implement complex systems with multiple interacting components, all following the **Model-View-Controller (MVC)** architecture.

---

## Key Features

* **Procedurally Generated World**: Each game instance dynamically generates a world with varying terrain, enemies, and health packs.
* **Dual View Interface**: Users can switch between a rich **Graphical View** and an efficient **Text View**.
* **Dynamic Gameplay**: Includes health and energy bars, difficulty adjustment slider, and multiple control options.
* **Multi-Level Progression**: Increasing difficulty and strategic challenges as the game progresses.
* **Advanced Enemy Behavior**: Enemies demonstrate unique behaviors like poison zones and knockback effects.
* **Autonomous Movement**: The protagonist can use a built-in pathfinding algorithm to reach goals automatically.

---

## Game Components

### World Elements

* **Tiles**: Represent different terrain types; each has unique energy costs.
* **Enemies**: Introduce risk and strategic depth. Types include:

  * **Standard Enemies**: Basic combatants.
  * **Poison Enemies (PEnemy)**: Emit an area of poison as they weaken.
  * **Bouncing Enemies (XEnemy)**: Knock the protagonist in random directions upon contact.
* **Health Packs**: Replenish the protagonist's health.

### Characters

* **Protagonist**: Controlled via keyboard, text commands, or mouse clicks.
* **Enemies**: Feature varying AI and interaction models.

---

## User Interface

### GUI Components

* **Main Window**: Switchable between Graphical and Text Views.
* **Graphical View**: Displays the game world with rich visuals (e.g., terrain, enemies, protagonist).
* **Text View**: ASCII-based representation with symbolic elements:

  * `@`: Protagonist
  * `E`, `P`, `X`: Enemy types
  * `H`: Health packs
  * `.`, `_`: Tiles with varying energy costs
* **Health and Energy Bars**: Track real-time resource levels.
* **Difficulty Slider**: Adjusts energy cost, enemy damage, and health pack recovery.
* **Command Input Box**: Supports auto-complete, case-insensitive text commands.
* **Mouse Control**: Click on tiles for quick movement.

---

## How to Play

### Controls

* **Arrow Keys**: Move the protagonist (Graphical View).
* **Text Commands**: Use abbreviated or full words (e.g., `r` + Tab = `right`).
* **Autoplay Button**: Trigger pathfinding-based movement.
* **Restart Button**: Reset the current world.
* **Mouse Click**: Move protagonist by selecting target tiles.

### Gameplay Tips

* Avoid enemies or defeat them strategically.
* Use health packs efficiently.
* Monitor your health and energy levels.
* Navigate to the level gate to proceed.
* Adjust difficulty based on your strategy.
* Game ends if health or energy reaches zero.

---

## Architecture

This project adheres to the **Model-View-Controller (MVC)** paradigm:

* **Model**: Game state and logic (World, Enemies, Tiles).
* **View**: GUI rendering (GraphicalView, TextView).
* **Controller**: User interaction and input (MainWindow, CommandHandler).

### Core Modules

* **World Module**: Procedural map and entity generation.
* **Pathfinder Module**: Implements A\* or similar algorithms for automated navigation.
* **MainWindow Module**: GUI management and event handling.
* **Game Model**: Maintains and updates the overall game state.

---

## Technologies Used

* **Qt Framework (C++)**
* **Object-Oriented Programming**
* **GUI & Event-Driven Design**
* **Algorithm Design (Pathfinding)**
* **MVC Software Architecture**

---

## UML Diagram

![UML Diagram](UML/UML_final.jpg)

---

## License

This project is licensed under the [MIT License](LICENSE).
