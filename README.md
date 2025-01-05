# Pokémon Simulation Game

This is my second C project, after I created my [first C-based game project](https://github.com/KyleCarlo/First-C-based-Mini-Game). 😊 I created this project to enhance my proficiency in using data structures.

This project simulates a simple Pokémon-like game, allowing players to enter Pokémon information and attempt to catch them during exploration. It features gameplay mechanics for managing a Pokédex, capturing Pokémon, and maintaining a storage box.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Gameplay Mechanics](#gameplay-mechanics)
- [Authors](#authors)

## Features

- Manage a custom Pokédex (FakeDex): Add, update, view, and remove Pokémon entries.
- Explore and attempt to catch Pokémon in the wild.
- Store caught Pokémon in a box with a limited capacity.
- Save and load game progress.
- Interactive menus and user-friendly interface with keyboard navigation.

## Requirements

- **C Compiler**: GCC or any standard C compiler.
- **Operating System**: Windows or Linux.
- **Libraries**: Standard C libraries (stdio.h, stdlib.h, string.h, etc.).

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/KyleCarlo/Fakedex.git
   ```
2. Navigate to the project directory:
3. Compile the source code:
   ```bash
   gcc -o fakedex fakedex.c
   ```
4. Run the compiled executable:

```bash
./fakedex
```

### Recommended Setup

For optimal graphics and better user experience, it is recommended to run the program using VSCode's integrated terminal rather than built-in system terminals.

NOTE: **Some of the graphics breaks if built-in terminal is used.**

### Controls

- Use arrow keys for navigation.
- Press **Enter** to confirm selections.
- Press **ESC** to cancel or exit certain menus.

## Gameplay Mechanics

### Main Menu Options

1. **FakeDex**:
   - Add, view, update, and remove entries.
2. **Exploration**:
   - Navigate tiles to encounter and catch Pokémon.
3. **Box**:
   - View and manage caught Pokémon.
4. **Settings**:
   - Save or load game progress.
5. **Exit**:
   - Terminate the game.

### FakeDex

- Each Pokémon entry includes the following:
  - Name
  - Nickname
  - Description
  - Gender
  - Caught Status

### Exploration

- Explore tiles to encounter Pokémon.
- Use items to catch Pokémon and add them to your box.

### Storage Box

- Holds a maximum of 100 Pokémon.
- Manage caught Pokémon by releasing or sorting them.

### Save & Load

- Save your progress to a file.
- Load previously saved files to continue your adventure.
  NOTE: **You can try to load the [saved file](`official_sav.txt) in the repository.**

## Authors

- Kyle Carlo C. Lasala
- Adam Martin S. Mendoza
