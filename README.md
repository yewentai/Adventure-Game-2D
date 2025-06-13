# Project: Adventure Game

## Overview

Welcome to our Adventure Game project! This is an interactive, graphics-based application designed to provide an
engaging gaming experience. It's built using Qt, a cross-platform application development framework, and incorporates
fundamental concepts like object-oriented programming, pathfinding algorithms, and GUI design.

### Key Features

- **Dynamic World Creation**: The game dynamically generates a world with varying terrain, enemies, and health packs.
- **Interactive GUI**: A rich graphical user interface (GUI) with switchable Grapical View and Text View, health and
  energy bars, dificculty adjustment slider and text-command input options.
- **Rich Graphics**: The game features a rich set of graphics, including the protagonist, enemies, health packs, and
  terrain.
- **Multiple Levels**: The game has multiple levels with increasing difficulty.
- **Enemy Behavior**: Enemies have different behaviors, including poison and boucing the protagonist.
- **Pathfinding Algorithm**: The protagonist can move automatically using the a pathfinding algorithm.

## Game Components

### The World

- **Tiles**: The basic unit of the game world, representing different terrain and consuming energy to traverse.
- **Enemies**: NPCs that the protagonist must defeat to recover energy or avoid to prevent health loss.
- **Health Packs**: Items to replenish the protagonist's health.

### Characters

- **Protagonist**: The main character controlled by the player by arrow keys on Graphical View or text commands on Text
  View or automatically by pathfinding algorithm.
- **Standard Enemies**: Regular enemies with basic behavior.
- **Poison Enemies (PEnemy)**: As poison enemies get closer to defeat, they release a weakening poison in a growing
  area. The poison disappears when the enemy dies. If the protagonist steps into the poison zone, they get poisoned, but
  it fades when they leave the contaminated area.
- **Bouncing Enemies (XEnemy)**: The enemies that bounce the protagonist away to a randon direction when the protagonist
  collides with them. After twice collision, the XEnemy will be destroyed.

### GUI Elements

- **Main Window**: Contains the Graphical View and Text View which can be switched by the buttons on the top.
- **Graphical View**: Displays the game world with rich graphics. TODO
- **Text View**: Displays the game world with ASCII characters. The protagonist is represented by ‘@’, enemies by ‘E’,
  Penemy by ‘P’, Xenemy by ‘X’, health packs by ‘H’, and tiles by ‘.’ and ‘_’. The strength of the enemies is
  represented by the color depth, while the energy consumption of the tiles is represented by the color brightness.
- **Health and Energy Bars**: Display the protagonist's current health and energy levels.
- **Difficulty Slider**: Adjusts the game's difficulty.
- **Command Input**: Allows command-based interactions for advanced players.

## How to Play

### Controls

- **Arrow Keys**: Move the protagonist in Graphical View.
- **Text Commands**: The command can be understood as soon as it is unique so typing a ‘r’ and pressing 'tab' will
  complete the command to ‘right’. And it is not case sensitive.
- **Autoplay Button**: Enable the protagonist to move automatically using pathfinding.
- **Restart Button**: Reset the game world.
- **Difficulty Slider**: Adjust the game's difficulty.
- **Click movement**: Click on a tile of choice for a more convenient control over the protagonist

### Game Mechanics

- Navigate through the world, avoiding or defeating enemies.
- Collect health packs to maintain your health.
- Manage your energy wisely, as moving consume energy.
- Reach the gate in each level to advance to the next level.
- The difficulty slider adjusts how much energy is consumed when moving, how much health is lost when colliding with
  enemies, and how much health is recovered when collecting health packs linearly.
- The game ends when the protagonist's health or energy reaches zero.

### Final UML

![image info](UML/UML_final.jpg)

### MVC Architecture

Implements the Model-View-Controller (MVC) architecture, ensuring separation of game logic, user interface, and user
input handling. The MVC architecture is implemented using the following modules and classes:

### Modules and Classes

- **World Module**: Handles the creation and management of the game world.
- **Pathfinder Module**: Implements the algorithm for navigation.
- **Main Window Module**: Manages the GUI and user interactions.
- **Game Model**: Represents the game logic and state.

## License

This project is licensed under the [MIT License](LICENSE).
