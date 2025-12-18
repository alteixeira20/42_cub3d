# CUB3D CONCEPTS (DEFENSE CHEATSHEET)
========================================================================

Purpose
-------
This document is a short, structured oral-defense guide for this repo.
Everything below is based strictly on the existing codebase.

If something is unclear in the code, it is explicitly called out.

========================================================================

1) HIGH-LEVEL ARCHITECTURE
--------------------------
Main loop
- `main` -> `startup` -> `mlx_loop`
- Each frame: `game_loop` -> `update_player` -> `draw_frame`
  Code: `src/main.c`, `src/loop.c`

Initialization
- `game_init` resets all structures (`t_game`)
- `parse_all` loads .cub (textures, colors, map, player)
- `render_init` creates MLX window + frame image
- `textures_load` loads XPM textures into runtime images
  Code: `src/init/init.c`, `src/parser/parser.c`,
        `src/render_init.c`, `src/render_textures.c`

Rendering pipeline
- For each screen column `x`:
  `ray_setup` -> `ray_dda` -> `ray_compute_lines`
  -> `ray_texcoords_setup` -> draw column
- Final image is pushed to the window each frame
  Code: `src/draw.c`, `src/raycast.c`

Input handling
- `key_press`/`key_release` only set flags in `t_input`
- `update_player` uses those flags to move/rotate
  Code: `src/input.c`, `src/update.c`

Data flow (structures)
- `t_game` is the single root state (`inc/cub3d.h`)
- `t_player`: position, direction, camera plane -> used by raycasting
- `t_map`: grid and dimensions -> used by DDA and collision
- `t_texture`: holds parsed file paths
- `t_rttex`: holds loaded MLX images used in rendering

========================================================================

2) MAP PARSING (.cub)
--------------------
Step-by-step
1. `parse_all` opens the file and reads line by line with GNL.
2. Each line is trimmed of newline by `line_dup_trimmed`.
3. `process_line` decides header vs map.
4. Header lines are parsed by `parse_texture` or `parse_color`.
5. Once all 6 IDs exist, the first map line starts map parsing.
6. All map lines are stored, then `parse_map` allocates the grid.
7. `parse_player` locates the player and sets direction.
8. `validate_map_closed` flood-fills to confirm enclosure.
   Code: `src/parser/parser.c`, `src/parser/parser_lines.c`,
         `src/parser/parser_map.c`, `src/parser/parser_player.c`,
         `src/validation/validation.c`

Element order independence
- `header_try_line` accepts `NO/SO/WE/EA/F/C` in any order
- The map only starts after all 6 IDs are set (`ids_complete`)
  Code: `src/parser/parser_lines.c`, `src/parser/parser_utils.c`

Texture identifiers (NO/SO/WE/EA)
- `parse_texture`:
  - rejects duplicates
  - trims spaces
  - enforces `.xpm`
  - verifies readable file
  Code: `src/parser/parser_textures.c`

Floor/Ceiling RGB parsing
- `parse_color` -> `color_assign`
- Strict `R,G,B` format with optional spaces
- Values must be 0..255
  Code: `src/parser/parser_color.c`

Map extraction and validation
- `parse_map` finds max width/height and allocates grid
- Each row is copied and padded
  Code: `src/parser/parser_map.c`

Space handling inside the map (important detail)
- In-line spaces are converted to `'0'` (walkable)
- Missing columns are padded with `' '` (void)
  Code: `src/parser/parser_map.c`

Wall enclosure logic
- `validate_map_closed` uses flood-fill from player position
- Any reach to `' '` or out-of-bounds => error
  Code: `src/validation/validation.c`

Errors and clean exit
- Any parser error calls `print_error` and returns `-1`
- File descriptor is closed and buffers are freed
  Code: `src/error/error.c`, `src/parser/parser.c`,
        `src/cleanup/cleanup.c`

========================================================================

3) RAYCASTING CORE (MOST IMPORTANT)
-----------------------------------
Ray direction calculation
- `camera_x = 2*x/SCR_W - 1`
- `ray_dir = dir + plane * camera_x`
  Code: `src/raycast.c` (`ray_setup`)

DDA algorithm
- `delta_x/y = fabs(1 / ray_dir_x/y)`
- `ray_set_dir` sets `step_x/y` and initial `side_dist_x/y`
- `ray_dda` advances the smallest side distance each step
  Code: `src/raycast.c`, `src/raycast_util.c`

Horizontal vs vertical hit detection
- `side == 0` => hit a vertical wall (x-side)
- `side == 1` => hit a horizontal wall (y-side)
  Code: `src/raycast.c` (`ray_dda`)

Wall distance calculation
- `perp_dist` uses grid intersection and `ray_dir`
- `line_h = SCR_H / perp_dist`
  Code: `src/raycast.c` (`ray_compute_lines`)

Why fish-eye happens
- Raw ray length is longer at screen edges, so walls look stretched.

How this project avoids fish-eye
- Uses perpendicular distance (`perp_dist`) for projection
  Code: `src/raycast.c`

========================================================================

4) TEXTURE MAPPING
------------------
Wall orientation (N/S/E/W)
- `ray_pick_tex` chooses texture based on `side` and ray sign
  Code: `src/raycast.c`

Texture X coordinate
- `wall_x` = exact hit position on the wall (fraction only)
- `tex_x = wall_x * tex_w`
- `tex_x` is flipped based on side and ray direction
  Code: `src/raycast.c` (`ray_texcoords_setup`)

Texture Y scaling
- `step = tex_h / line_h`
- `tex_pos` starts at the top of the wall slice
- Increment by `step` each screen pixel
  Code: `src/raycast.c`

Pixel writing
- `get_texel` reads from texture image buffer
- `put_pixel` writes to frame buffer
  Code: `src/draw.c`

========================================================================

5) MOVEMENT & COLLISION
-----------------------
Player position updates
- Inputs build a movement vector
- Vector is normalized and scaled by movement speed
  Code: `src/update.c`

Collision with walls
- `is_blocked` checks 4 points around the player (`COLL_R`)
- Blocks on walls or out-of-bounds
  Code: `src/update.c`

Why diagonal movement does not clip
- X and Y are applied separately (axis-based collision)
  Code: `src/update.c`

Rotation logic
- `rotate_left/right` rotates both direction and camera plane
  Code: `src/update_util.c`

========================================================================

6) MINILIBX & RENDERING LOOP
----------------------------
Image buffer usage
- A single MLX image (`render.frame`) is drawn every frame
  Code: `src/render_init.c`, `src/draw.c`

Double buffering
- The frame is drawn offscreen and then blitted to the window
  Code: `src/draw.c`

Images destroyed / recreated
- Frame image is created in `render_init` and destroyed in `render_destroy`
- Texture images are created in `textures_load` and destroyed in
  `textures_destroy`
  Code: `src/render_init.c`, `src/render_textures.c`

Window close and ESC handling
- ESC in `key_press` triggers `win_close`
- Window close event (17) also triggers `win_close`
  Code: `src/input.c`, `src/loop.c`

========================================================================

7) NORM & SAFETY
----------------
Memory ownership rules
- Texture paths are allocated in parsing and freed by `clean_texture`
- Map grid is allocated in `parse_map` and freed by `clean_map`
- Temporary line buffers are freed by `clean_map_buffer`
  Code: `src/parser/parser_textures.c`, `src/parser/parser_map.c`,
        `src/cleanup/cleanup_util.c`, `src/cleanup/cleanup.c`

Malloc/free symmetry
- `clean_game` and `clean_game_setup` mirror allocations from
  parsing and rendering
  Code: `src/cleanup/cleanup.c`

Segmentation fault avoidance
- DDA bounds check in `ray_dda`
- Collision bounds check in `is_blocked`
- Division by zero avoided in `ray_setup` with huge delta
- Texture Y clamped before access
  Code: `src/raycast.c`, `src/update.c`, `src/draw.c`

Clean exit paths
- Parsing errors: print error, free buffers, close fd
- Runtime exit: `win_close` -> `clean_game` -> `exit(0)`
  Code: `src/parser/parser.c`, `src/loop.c`

========================================================================

8) EVALUATION DEFENSE MODE
--------------------------
Top 10 likely evaluator questions + concise answers
1) How do you compute ray direction per column?
   - `camera_x = 2*x/SCR_W - 1`,
     `ray_dir = dir + plane * camera_x`
   Code: `src/raycast.c`

2) Where is the DDA loop?
   - In `ray_dda`, advancing by smaller side distance until a wall is hit
   Code: `src/raycast.c`

3) How do you avoid fish-eye distortion?
   - Use `perp_dist` (perpendicular distance) for wall height
   Code: `src/raycast.c`

4) How do you decide which wall texture to use?
   - `ray_pick_tex` uses hit side and ray direction sign
   Code: `src/raycast.c`

5) How do you parse .cub headers in any order?
   - `header_try_line` accepts any ID before map starts
   Code: `src/parser/parser_lines.c`

6) When does the map start?
   - Only after all 6 IDs exist (`ids_complete`)
   Code: `src/parser/parser_lines.c`, `src/parser/parser_utils.c`

7) How is map closure validated?
   - Flood-fill from player; reaching void or edge is invalid
   Code: `src/validation/validation.c`

8) How is collision handled?
   - `is_blocked` checks 4 points with radius and blocks walls
   Code: `src/update.c`

9) Where are pixels written?
   - `put_pixel` writes into `render.frame` then blits to window
   Code: `src/draw.c`

10) What happens on ESC / window close?
   - `win_close` frees and exits
   Code: `src/input.c`, `src/loop.c`

3 areas an evaluator may dig deeper
1) Player direction for E/W
   - `set_dir_and_plane_ea/we` sets dir/plane to zero.
     This is unclear in the code and should be explained carefully.
   Code: `src/parser/parser_player_dir.c`

2) Space handling in map
   - In-line spaces become `'0'`, while padding becomes `' '`.
     This changes walkable vs void behavior.
   Code: `src/parser/parser_map.c`

3) Unused error constant
   - `ERR_MAP_AFTER_CONTENT` exists but no code path uses it.
   Code: `inc/cub3d.h`, `src/parser/parser_lines.c`

3 common mistakes this project avoids
1) Fish-eye distortion (uses perpendicular distance)
   Code: `src/raycast.c`
2) Duplicate IDs or invalid colors (strict parsing)
   Code: `src/parser/parser_textures.c`, `src/parser/parser_color.c`
3) Diagonal wall clipping (axis-separated movement)
   Code: `src/update.c`

========================================================================

End of document.
