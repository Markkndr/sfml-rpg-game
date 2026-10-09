<div align="center">

# ⚔️ ProjectRPG 🧙

### A top-down 2D action RPG built from scratch in C++ and SFML

A hand-rolled game engine and RPG: a state-driven game loop, component-based entities, a tile map with its own in-game level editor, and dynamic GLSL lighting that follows the player through the dark.

<br>

<img src="https://img.shields.io/badge/Status-In_Progress-orange?style=for-the-badge" alt="Status: In Progress">
<img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" alt="C++">
<img src="https://img.shields.io/badge/SFML-2.6.1-8CC445?style=for-the-badge&logo=sfml&logoColor=white" alt="SFML 2.6.1">
<img src="https://img.shields.io/badge/GLSL-Shaders-5586A4?style=for-the-badge&logo=opengl&logoColor=white" alt="GLSL Shaders">
<img src="https://img.shields.io/badge/Visual_Studio-2026-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white" alt="Visual Studio 2026">
<img src="https://img.shields.io/badge/Platform-Windows_x64-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Platform: Windows x64">
<img src="https://img.shields.io/badge/License-MIT-blue?style=for-the-badge" alt="License: MIT">

</div>

> 🚧 **This project is under active development.** See [**Current Status**](#-current-status) for what's implemented and the [**Roadmap**](#-roadmap) for what's next.

---

## 📑 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Controls](#-controls)
- [Tech Stack](#-tech-stack)
- [Architecture](#-architecture)
- [Current Status](#-current-status)
- [Roadmap](#-roadmap)
- [Getting Started](#-getting-started)
- [Configuration](#-configuration)
- [Project Structure](#-project-structure)
- [License](#-license)

---

## 🎯 About

**ProjectRPG** is a 2D action RPG written in C++ on top of [SFML](https://www.sfml-dev.org/) — no game engine, just a custom framework built piece by piece: the game loop, state management, entity components, collision, animation, GUI widgets, and rendering pipeline are all implemented by hand.

You play as a witch exploring a tile-based world, casting spells at the cursor while a shader-driven light source around the character pushes back the darkness. The world itself is authored with a **built-in level editor** that saves and loads maps from plain-text files.

---

## ✨ Features

- 🔁 **State-stack game loop** — main menu, game, settings, and editor states pushed and popped on a stack, with a frame-rate-independent delta-time update loop
- 🧩 **Component-based entities** — players and enemies are composed from reusable **movement**, **hitbox**, **animation**, and **attribute** components
- 🏃 **Physics-style movement** — acceleration, deceleration, and max-velocity tuning with directional movement states
- 🎞️ **Sprite-sheet animation** — named animations with per-animation speed, velocity-scaled playback, and priority animations (e.g. attacks that can't be interrupted)
- 🪄 **Spell casting** — click to cast at the mouse position, with a dedicated attack animation and spell hitbox
- 📈 **RPG progression** — level, EXP with a cubic level curve, stat points, and derived stats (HP, attack damage, ability power, movement and attack speed) from **Strength / Intelligence / Agility**
- ❤️ **Player HUD** — level badge, HP bar, and EXP bar
- 🗺️ **Layered tile map** — 3D grid of tile stacks with per-tile collision and tile types (`DEFAULT`, `DAMAGING`, `DEFERRED`)
- ⚡ **View culling** — only tiles around the camera are rendered, and only tiles around each entity are checked for collision
- 🌳 **Deferred tiles** — `DEFERRED` tiles render *after* entities, so the player can walk behind trees and props
- 💡 **Dynamic lighting** — a GLSL vertex/fragment shader pair renders a point light centred on the player over a dark ambient scene
- 🎥 **Mouse-look camera** — the view follows the player and leans toward the cursor, clamped to the world bounds
- 🛠️ **In-game level editor** — pick tiles from a texture-sheet selector, paint and erase on the grid, toggle collision, set tile types, and save/load maps
- ⚙️ **Settings menu** — resolution drop-down populated from the monitor's supported video modes
- ⌨️ **Data-driven keybinds** — every state reads its key mappings from `.ini` files, so controls can be remapped without recompiling
- 📐 **Resolution-independent GUI** — buttons, drop-downs, and text are sized as percentages of the current resolution

---

## 🎮 Controls

### In game

| Input | Action |
|-------|--------|
| `W` `A` `S` `D` | Move |
| `Left Mouse` | Cast a spell at the cursor |
| `Mouse` | Lean the camera toward the cursor |
| `Esc` | Pause / unpause (pause menu → Exit) |

<details>
<summary>🐞 Debug keys</summary>

| Key | Action |
|-----|--------|
| `P` | Gain 1 HP |
| `L` | Lose 1 HP |
| `F` | Gain 5 EXP (hold) |

</details>

### Level editor

| Input | Action |
|-------|--------|
| `W` `A` `S` `D` | Move the camera |
| `Left Mouse` | Place the selected tile / pick a tile in the texture selector |
| `Right Mouse` | Remove a tile |
| `C` | Toggle collision for placed tiles |
| `↑` / `↓` | Change tile type |
| `Esc` | Pause menu → **Save**, **Load**, or **Exit** |

> All game and editor keybinds are configurable — see [Configuration](#-configuration).

---

## 🛠 Tech Stack

| Layer | Technology |
|-------|-----------|
| **Language** | C++ |
| **Multimedia** | SFML 2.6.1 (graphics, window, system, audio, network), statically linked |
| **Rendering** | OpenGL via SFML, GLSL vertex + fragment shaders, off-screen `sf::RenderTexture` |
| **Build** | Visual Studio 2026 (MSVC toolset v145), Windows x64 |
| **Data** | Plain-text `.ini` config files and `.map` tile-map files |

> SFML 2.6.1 headers and static libraries are vendored in [`dependencies/SFML`](dependencies/SFML), so no separate SFML install is required.

---

## 🏗 Architecture

### Game loop & state stack

`Game` owns the window and a `std::stack<State*>`. Every frame it updates delta time, polls events, and updates/renders **only the top state**. States push new states (e.g. the main menu pushes `GameState`) and quit by flagging themselves for removal.

```
  main() ──► Game::Run()
               │  every frame:  updateDt → updateSFMLEvents → update → render
               ▼
        ┌────────────────┐
        │  State stack   │      top state receives update(dt) / render()
        ├────────────────┤
        │ GameState      │ ◄── pushed from main menu
        │ MainMenuState  │ ──► also pushes SettingState / EditorState
        └────────────────┘
  Shared StateData: window, graphics settings, supported keys, grid size, state stack
```

### Entities & components

```
               Entity  (sprite + optional components)
              ┌───┴────────┐
           Player       Enemies
              │
  ┌───────────┼─────────────┬──────────────────┐
  ▼           ▼             ▼                  ▼
Movement   Hitbox       Animation          Attribute
(velocity, (collision   (sprite-sheet      (level, EXP,
 accel,     bounds)      animations,        STR/INT/AGI,
 decel)                  priority)          derived stats)
```

### Rendering pipeline

`GameState` renders the scene into an off-screen `sf::RenderTexture` and then draws it to the window as a single sprite:

```
  1. Tile map (culled to the view)       ─┐
  2. Enemies                              ├─ drawn through the lighting shader,
  3. Player (+ spell hitbox)              │   light source = player centre
  4. Deferred tiles (trees, props)       ─┘
  5. HUD (HP / EXP / level) and pause menu, in screen space
  ──► renderTexture.display() ──► window
```

---

## ✅ Current Status

Implemented so far:

- 🔁 **Core engine** — game loop, delta time, state stack, shared state data
- 🖥️ **Menus** — main menu, settings (resolution drop-down), and pause menus for the game and editor
- 🧩 **Entity component system** — movement, hitbox, animation, and attribute components
- 🧙 **Player** — movement, idle/run/attack animations with sprite flipping, mouse-aimed spell casting
- 📈 **Attributes & levelling** — EXP, level-ups, stat points, and derived stats, shown on the HUD
- 🗺️ **Tile map** — layered grid, culling, collision resolution, deferred tiles, and map save/load
- 🛠️ **Level editor** — texture selector, paint/erase, collision and tile-type editing, save/load to `config/test.map`
- 💡 **Lighting** — GLSL point light following the player over a dark ambient scene
- 👾 **Enemies** — an animated enemy entity with collision against the tile map

---

## 🗺 Roadmap

- 🏰 **Procedural dungeon generation** — rooms, corridors, and exits (`MapGeneration` is scaffolded)
- 👾 **Enemy AI** — movement, pathing, and aggro toward the player
- ⚔️ **Combat** — spell damage on hit using the attribute stats, enemy health, and death animations
- 🔥 **Damaging tiles** — apply damage to entities standing on `DAMAGING` tiles
- 🧮 **Stat allocation** — spend stat points on Strength, Intelligence, or Agility
- 🗂️ **Multi-layer editing** — place tiles on layers above the ground layer in the editor
- 💾 **Persistent settings** — write graphics changes back to `config/graphics.ini`
- 🔊 **Audio** — music and sound effects via SFML Audio

---

## 🚀 Getting Started

### Prerequisites

- **Windows 10/11 (x64)**
- **Visual Studio 2026** with the **Desktop development with C++** workload (MSVC toolset v145)

SFML is bundled in the repository, so there's nothing else to install.

### Build & run

```bash
git clone https://github.com/Markkndr/ProjectRPG.git
```

1. Open `ProjectRPG.sln` in Visual Studio.
2. Select the **x64** platform and either **Debug** or **Release**.
3. Press **F5** to build and run.

The executable is written to `Build/x64/<Configuration>/bin/`.

> ⚠️ The game loads `assets/`, `config/`, and the shaders in `src/` using paths relative to the **`ProjectRPG/` project folder**. Running from Visual Studio sets this up automatically. To launch the `.exe` directly, run it with `ProjectRPG/` as the working directory.

---

## ⚙️ Configuration

All configuration lives in [`ProjectRPG/config/`](ProjectRPG/config):

| File | Purpose |
|------|---------|
| `graphics.ini` | Window title, resolution, fullscreen, V-sync, frame-rate limit, anti-aliasing level |
| `gamestate_keybinds.ini` | In-game controls |
| `editorstate_keybinds.ini` | Level editor controls |
| `mainmenustate_keybinds.ini` | Main menu and settings menu controls |
| `player_keybinds.ini` | Player controls (reserved — not loaded yet; movement uses `gamestate_keybinds.ini`) |
| `supported_keys.ini` | Maps key names to SFML key codes — the vocabulary the keybind files use |
| `test.map` | The current world, written by the level editor |

### `graphics.ini`

One value per line:

```ini
ProjectPRG      ; window title
1920 1080       ; resolution (width height)
0               ; fullscreen (0/1)
0               ; V-sync (0/1)
165             ; frame-rate limit
0               ; anti-aliasing level
```

> The `;` comments above are for illustration only — the file itself must contain just the values.

### Keybinds

Each line maps an action to a key name from `supported_keys.ini`:

```ini
CLOSE Escape
MOVE_UP W
MOVE_DOWN S
MOVE_LEFT A
MOVE_RIGHT D
```

### Map format

`.map` files are plain text: a header with the world size, grid size, layer count, and tile-sheet path, followed by one entry per tile:

```
<grid x> <grid y> <layer> <texture rect x> <texture rect y> <collision> <type>
```

---

## 📂 Project Structure

```
ProjectRPG/
├── ProjectRPG.sln
├── dependencies/
│   └── SFML/                  # Vendored SFML 2.6.1 headers & static libs
└── ProjectRPG/
    ├── ProjectRPG.vcxproj
    ├── assets/
    │   ├── enemies/textures/  # Enemy sprite sheets
    │   ├── fonts/             # UI font
    │   ├── menu/              # Main menu background
    │   ├── player/textures/   # Player sprite sheets
    │   └── world/textures/    # Tile sheets, props, plants, trees, water
    ├── config/                # Graphics settings, keybinds, map files
    └── src/
        ├── main.cpp, Game.*               # Entry point, window, game loop, state stack
        ├── State.*                        # Abstract state + shared StateData
        ├── MainMenuState.*                # Main menu
        ├── GameState.*                    # Gameplay, camera, deferred rendering
        ├── EditorState.*                  # Level editor
        ├── SettingState.*                 # Settings menu
        ├── PauseMenu.*                    # Pause overlay
        ├── Entity.*, Player.*, Enemies.*  # Entities
        ├── MovementComponent.*            # Velocity / acceleration
        ├── HitboxComponent.*              # Collision bounds
        ├── AnimationComponent.*           # Sprite-sheet animation
        ├── AttributeComponent.*           # Levels, EXP, stats
        ├── TileMap.*, Tile.*              # Tile map, culling, collision, save/load
        ├── MapGeneration.*                # Procedural generation (in progress)
        ├── Gui.*, PlayerGUI.*             # Buttons, drop-downs, texture selector, HUD
        ├── GraphicsSettings.*             # graphics.ini loading
        ├── vertex_shader.vert             # Lighting — vertex stage
        ├── fragment_shader.frag           # Lighting — fragment stage
        └── stdafx.*                       # Precompiled header
```

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

> The MIT License covers the source code. SFML is distributed under its own [zlib/png license](https://www.sfml-dev.org/license.php), and third-party art in `assets/` remains under its original creators' terms.

---

<div align="center">

Built tile by tile, one frame at a time. 🗡️✨

</div>
