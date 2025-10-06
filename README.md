<p align="center">
  <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C badge">
  <img src="https://img.shields.io/badge/MiniLibX-5C6BC0?style=for-the-badge&logo=opengl&logoColor=white" alt="MiniLibX badge">
  <img src="https://img.shields.io/badge/Make-427819?style=for-the-badge&logo=cmake&logoColor=white" alt="Make badge">
  <img src="https://img.shields.io/badge/Shell-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Shell badge">
  <img src="https://img.shields.io/badge/Valgrind-773344?style=for-the-badge&logo=gnu&logoColor=white" alt="Valgrind badge">
  <img src="https://img.shields.io/badge/GDB-800000?style=for-the-badge&logo=gnu&logoColor=white" alt="GDB badge">
</p>

<h1 align="center">cub3D</h1>
<p align="center">Ray-casted maze runner with responsive controls, immersive textures, and a self-diagnosing tester suite.</p>

<p align="center"><sub><em style="color:#888888;">Project still in development — built by alteixeira20 and <a href="https://github.com/4Rr0x">jopedro-</a>.</em></sub></p>

<p align="center">
  <img src="docs/images/running_game.gif" alt="Live gameplay preview" width="85%" />
  <br />
  <em>Live preview of the current gameplay loop.</em>
</p>

## Table of Contents
1. [At a Glance](#at-a-glance)
2. [About](#about)
3. [Subject Compliance](#subject-compliance)
4. [Custom Tester](#custom-tester)
5. [Repository Layout](#repository-layout)
6. [Build & Integration](#build--integration)
7. [Usage Guidelines](#usage-guidelines)
8. [Feature Deep Dive](#feature-deep-dive)
9. [Input & Animation](#input--animation)
10. [Rendering & HUD](#rendering--hud)
11. [Internal Architecture](#internal-architecture)
12. [Tester Workflow](#tester-workflow)
13. [Results & Reporting](#results--reporting)

## At a Glance
> **Highlights:** Completely autonomous raycaster with defensive parsing, evaluation-ready tooling, and intentionally smooth locomotion.

- Mandatory loop mirrors Wolfenstein 3D: textured walls, real-time pitch, keyboard-only input, graceful exit paths.
- Movement profiling pays off: simultaneous `W+A+S+D` strafes stay responsive while the camera glides through a full 360° sweep without visible stutter.
- Bonus build unlocks doors, collectibles, minimap overlays, HUD counters, and animated sprites without breaking subject rules.
- One `Makefile` drives everything: libft fetch/build, MiniLibX compilation, standard & bonus executables, and diagnostic testers.
- Project ships with curated invalid/valid scenes, tester automation, and Git-friendly assets to accelerate peer reviews.

## About
> **Highlights:** Purpose-built for 42 Porto’s first-person graphics milestone.

- Implements a full raycasting pipeline in C using MiniLibX to render a 1920×1080 viewport at interactive speeds.
- Leverages a modular parser to read `.cub` scene files, normalize spaces to walkable floor, and enforce all subject-required identifiers.
- Bonus feature set focuses on readability: minimap zoom, door state interpolation, collectible animations, and HUD counters for keys.
- Co-developed with <a href="https://github.com/4Rr0x">jopedro-</a>; we review each feature together to keep the codebase approachable while we iterate.

## Subject Compliance
> **Highlights:** Every mandatory bullet of the subject PDF is covered and auditable.

- `.cub` loader validates identifiers (`NO/ SO/ WE/ EA/ F/ C`), detects duplicate/missing entries, and guarantees readable `.xpm` textures.
- Map parser enforces rectangularity, sealed boundaries, unique player spawn, and safe dimensions (`8192×8192` max) before gameplay begins.
- Game loop respects official controls (`WASD`, arrow keys, `ESC`, window close), updates steering smoothly, and frees all resources on exit.
- Floor/ceiling colors are clamped per RGB component; invalid numeric ranges or trailing characters halt the run with explicit errors.

## Custom Tester
> **Highlights:** Built-in automation keeps evaluations consistent and transparent.

<p align="center">
  <img src="docs/images/running_tester.gif" alt="Custom tester execution" width="70%" />
  <br />
  <em>Custom tester showcasing automated invalid-map and texture sweeps.</em>
</p>

- `make tester` chains `test_invalid` and `test_textures` to scrutinize failure handling and leak hygiene with Valgrind.
- Tester iterates curated invalid scenes, checks for the mandatory `Error` header plus a descriptive second line, and reports pass/fail tallies.
- Texture tests temporarily remove read permissions from every `.xpm` (map walls + collectibles) to ensure the engine surfaces the offending filename.
- Automation skips noise: it cleans temp files, restores permissions, and only prints actionable verdicts for quick debugging.

## Repository Layout
> **Highlights:** Clear separation between engine, bonus mechanics, and tooling.

- `src/` — Mandatory build: init, parser, validation, rendering, input loop, and cleanup helpers.
- `src_bonus/` — Bonus-exclusive systems (doors, minimap, collectibles, HUD, mouse input) mirroring the mandatory structure.
- `inc/` — Shared headers `cub3d.h` & `cub3d_bonus.h` with macros, error messages, structs, and prototypes.
- `mlx/` & `libft/` — Vendor code fetched/compiled automatically by the Makefile.
- `maps/valid` & `maps/invalid` — Reference scenes, including oversize stress tests (`invalid_map_width.cub`, `invalid_map_height.cub`).
- `docs/` — Official subject PDF plus trimmed gameplay videos; `images/` contains autoplay-ready GIFs for documentation.

## Build & Integration
> **Highlights:** Single Makefile handles dependencies, binaries, and diagnostics.

```sh
# Build mandatory target
make

# Build bonus target (doors, minimap, collectibles)
make bonus

# Launch the tester suite
make tester

# Launch Test of Invalid Map Formats
make test_invalid

# Launch Test of Invalid/Missing Texture
make test_textures

# Clean / rebuild helpers
make clean    # remove objects
make fclean   # clean + binaries + libft clone
make re       # rebuild from scratch
```

- `make` clones libft on demand, compiles MiniLibX silently, and links the mandatory executable at `./cub3D`.
- `make bonus` reuses the same dependency flow for `./cub3D_bonus` with the extended feature set.
- Valgrind presets (`make valgrind`, `make valgrind_bonus`, `make valgrind_invalid`) provide leak and UB checks without extra setup.

## Usage Guidelines
> **Highlights:** Ship-ready binaries with preset maps and keyboard-centric controls.

- Run the game by pointing to any `.cub` scene:
  ```sh
  ./cub3D maps/valid/map1.cub
  ./cub3D_bonus maps/valid/map_with_keys.cub
  ```
- Use `make maps` for an interactive launcher that lets you choose executable (mandatory/bonus) and browse valid or invalid maps.
- Keyboard layout:
  - `W/S` move forward/backward, `A/D` strafe, arrow keys rotate view.
  - `ESC` or the window close button terminate cleanly.
  - Bonus build adds `M` to toggle pause/mouse capture, door proximity triggers, and collectible pick-ups.

## Feature Deep Dive
> **Highlights:** Every subsystem is auditable through optional deep dives.

<details>
<summary>Parsing & Validation</summary>

- `parse_all` streams the `.cub` file, trims carriage returns, and categorizes lines before touching map content.
- Lines buffer collects map rows while preserving visual layout—spaces become floor (`'0'`), padding remains `' '` to guard boundaries.
- Texture loader confirms `.xpm` extension after trimming, rejects unreadable paths, and frees memory on failure.
- Flood-fill seal check duplicates the grid and ensures the player spawn is completely enclosed before gameplay.
</details>

<details>
<summary>Raycasting & Collision</summary>

- `ray_setup`, `ray_dda`, and `ray_compute_lines` implement classic DDA raycasting with perpendicular distance correction to avoid fish-eye distortion.
- Door slices reuse ray state: when a ray hits an open door, a secondary search finds the backing wall to render correct parallax.
- Movement normalizes combined direction vectors, scales by `ms = 0.07` (mandatory) or `PLAYER_MOVE_SPEED` (bonus), and checks four collision corners using `COLL_R`.
</details>

<details>
<summary>Bonus Gameplay Systems</summary>

- Doors fade via `DOOR_OPEN_SPEED` and `door_plane_offset`, while `update_doors_for_frame` syncs animations per frame.
- Collectibles employ preloaded sprite frames (`assets/key/`) with bobbing and phase offsets to keep motion varied.
- Minimap samples the world using a 2×2 anti-aliased approach, draws the player marker, and can be toggled/panned via configuration.
</details>

## Input & Animation
> **Highlights:** Smooth keyboard steering with optional mouse look and pitch.

- Mandatory build manages `t_input` flags for `WASD` + arrows; rotation helpers (`rotate_left/right`) rely on cosine/sine updates, even when combining strafes for diagonal movement.
- Bonus input captures the X pointer delta for mouse yaw, clamps pitch (`±0.5`) to prevent gimbal lock, and hides the cursor while active.
- Camera yaw handles full 360° sweeps while walking, so panning and locomotion remain in sync and free of visible hitching.
- Animation loops include door interpolation, key sprite advancements (12 FPS) via `collectibles_update`, and player pitch offsets in view calculations.

## Rendering & HUD
> **Highlights:** Layered presentation keeps the frame clean and informative.

- Texture sampling uses `get_texel` with side-based shadowing to emphasize depth; floor/ceiling colors fill above/below the column gracefully.
- Bonus rendering calls `draw_frame` to stack door slices, collectibles, HUD text, minimap, and crosshair over the raycast background.
- Minimap sampling stays locked to the player—even during mouse-only camera spins—so your marker, door arcs, and nearby walls reflect real-time movement without jitter.
- HUD labels render through custom bitmap fonts (`ui/hud/hud_text.c`) and summarize collected keys versus total available.

## Internal Architecture
> **Highlights:** Predictable modules make debugging painless.

- Initialization (`src/init`, `src_bonus/init`) zeroes textures, player state, render buffers, and input structs.
- Cleanup routines (`clean_game`, `clean_keys`, `clean_doors`) ensure every malloc’d buffer or MiniLibX image is freed on both normal and error exits.
- Core structs (`t_game`, `t_render`, `t_ray`, `t_collectibles`) centralize runtime state; helpers access them via clear, single-responsibility functions.
- Build system isolates object folders (`obj`, `obj_bonus`) to keep mandatory and bonus artifacts from colliding.

## Tester Workflow
> **Highlights:** Automation doubles as documentation and safety net.

- `test_invalid` loops through `maps/invalid`, asserts the two-line error contract, and runs Valgrind with `--error-exitcode=42` to catch leaks.
- `test_textures` toggles file permissions per texture, reruns the chosen executable, and checks that the offending filename is cited in the error text.
- Both testers maintain pass/fail counters, skip missing assets, and exit non-zero if any case fails—perfect for CI hooks or peer review scripts.
- The `running_tester.gif` provides an at-a-glance view for evaluators on how verdicts appear in real time.

## Results & Reporting
> **Highlights:** Output stays focused on decision-grade information.

- Gameplay sessions log only critical events: parsing success, runtime errors, and cleanup confirmations—no noisy debug spam.
- Tester logs print succinct per-map verdicts plus a final summary line (e.g., `Passed 23 tests and 0 tests.`) so issues are immediately visible.
- Valgrind integrations suppress known MiniLibX noise (`valgrind.supp`) and bubble up leaks or invalid reads with actionable diffs.
