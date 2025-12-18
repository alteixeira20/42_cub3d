# Cub3D Glossary

Compact reference for the bonus build. Sections open/close with the arrows. All paths point to `src_bonus/` and `inc/cub3d_bonus.h`.

<details>
<summary>Architecture</summary>

- Entry: `main` → `startup` → MLX loop (hooks in `main.c`).
- Root state: `t_game` aggregates map, player, textures, doors, collectibles, minimap, render images, z-buffer, and input.
- Modules: init, parser, validation, render, raycast, update, game overlays, UI, collectibles, cleanup, input.
</details>

<details>
<summary>Program Flow</summary>

- Init: `game_init` zeroes structs → `parse_all` loads `.cub` → `render_init_win` creates MLX/window/frame → `textures_load` + `keys_load` → `minimap_init`.
- Loop (`game/loop.c`):
  - Start screen until `ENTER`.
  - Running: `update_player` then `draw_frame`.
  - Pause: dim frame + pause XPM.
  - End: dim frame + end XPM after all keys collected.
- Exit: `win_close` on ESC or window close → `clean_game` → `exit(0)`.
</details>

<details>
<summary>Parsing & Validation</summary>

- Lines read with GNL, trimmed (`line_dup_trimmed`).
- Headers: `NO/SO/WE/EA/DO/F/C` in any order before map; `.xpm` enforced; duplicates rejected; colors `R,G,B` 0–255.
- Map: buffer lines then allocate padded grid; inline spaces → `'0'`; pad beyond line length → `' '`; width/height caps enforced.
- Player: one spawn, centered at `tile+0.5`; dir/plane set by `N/S/E/W`.
- Doors: every `D` stored in `t_doors` with `open_t`.
- Collectibles: every `C` stored with phase offset for bobbing.
- Validation: extension checks; flood-fill from player fails on void/OOB; adjacent doors rejected.
</details>

<details>
<summary>Raycasting (Walls & Doors)</summary>

- Setup: `camera_x = 2*x/SCR_W - 1`; `ray_dir = dir + plane * camera_x`; `delta = fabs(1/ray_dir)` (or `1e30` if zero); `ray_set_dir` sets steps and first side distances.
- DDA: step along the smaller side distance; stop on `'1'` (wall) or a blocking `'D'`; out-of-bounds exits safely.
- Projection: perpendicular distance by hit axis removes fish-eye; `line_h = SCR_H / perp_dist`; pitch offsets `draw_start/end`.
- Doors: first door hit stored per column; `ray_find_wall_behind_door` continues to the backing wall when doors are open; `door_plane_offset` + `apply_door_sink` lower the visible slice and shift texture Y based on openness.
</details>

<details>
<summary>Rendering Pipeline</summary>

- Per column: raycast → choose texture (NO/SO/WE/EA/DO) → compute slice → apply door sink → set texcoords → draw ceiling/wall/floor → record `zbuf[x]`.
- Door layer: after walls, `render_doors` redraws stored door rays so doors appear in front of farther walls.
- Texture coords: `wall_x` fractional hit; `tex_x` flipped on backfaces; vertical step = `tex_h/line_h`; pitch included.
</details>

<details>
<summary>Sprites (Collectibles)</summary>

- Projection: `sprite_transform` converts world to camera space; screen X from plane/direction; height/width scale with distance.
- Bounds: `sprite_bounds` clamps to screen; stripes drawn only if depth < `zbuf[x]`.
- Animation: 24 frames at `KEY_ANIM_FPS`; bobbing via `sin(anim_t*2 + phase)` for variation.
</details>

<details>
<summary>HUD & Overlays</summary>

- HUD: bitmap glyphs draw “Collected X/Y”; positioned via `hud_init` and `hud_put_text`.
- Crosshair: simple plus at center.
- Overlays: start/pause/end XPMs centered over the frame; `overlay_dim_frame` halves RGB for dimming; `overlay_blit_centered` handles transparency; start shows “Press ENTER to start”.
</details>

<details>
<summary>Minimap</summary>

- Image anchored top-right; size from `MM_RADIUS_TILES`, `MM_TILE_SIZE`, `MM_SCALE`.
- Sampling uses player dir/plane so the view rotates with the camera.
- Anti-alias: `sample2x2` averages four offsets (with `MM_SS_OFFSET`) for smoother lines.
- Colors: walls, floor/collectibles, void, player marker, border.
</details>

<details>
<summary>Player & Camera</summary>

- State: position, dir, camera plane, pitch, spawn dir char.
- Movement: flags build a vector from dir (forward/back) and plane (strafe); normalized, scaled by `PLAYER_MOVE_SPEED`; X/Y applied separately; collision checks four corners against walls/closed doors/OOB.
- Rotation: mouse yaw accumulates and rotates dir/plane once per frame; pitch from mouse Y delta, scaled by sensitivity, clamped to [-0.5, 0.5], used in projection.
</details>

<details>
<summary>Input</summary>

- Keyboard: `W/A/S/D` move; `ENTER` start; `P` pause/unpause (toggles mouse capture); `ESC` exits.
- Mouse: when captured, cursor hidden and recentered; dx → yaw; dy → pitch; released on pause/end.
</details>

<details>
<summary>Bonus Systems (Doors & Collectibles)</summary>

- Doors: `open_t` grows when player within `DOOR_RADIUS` and shrinks otherwise; `DOOR_OPEN_SPEED` controls rate. Collision and DDA block until fully open. Rendering sinks slice and can reveal the wall behind an open doorway.
- Collectibles: keys parsed from `C`, frames preloaded from `assets/key/`; pickup within `KEY_PICKUP_DIST`; increments counter; when all collected, `game_over` shows end overlay and releases mouse.
</details>

<details>
<summary>Memory & Cleanup</summary>

- Allocated: map rows, texture paths, door array, collectible array, MLX images (frame, minimap, overlays, wall/door textures, key frames).
- Cleanup: `clean_game_setup` for early parse failure; `clean_game` frees textures (`textures_destroy`), keys (`clean_keys`), minimap image, overlays, map, doors, collectibles, then destroys MLX display/window.
- Valgrind: X11/MLX keep reachable caches (visuals, cursors, fonts); covered in `valgrind.supp`.
</details>

<details>
<summary>Error Handling</summary>

- Parse errors: print `Error` + message, close file, free buffered lines, unwind allocations.
- Prechecks: `textures_precheck`/`keys_precheck` reopen every path right before MLX load to fail early on unreadable files.
- Runtime: `win_close` is the single exit path for ESC or window close.
</details>

<details>
<summary>Quick References</summary>

- Ray math: `raycast_init`, `ray_dda`, `ray_compute_lines`, `ray_texcoords_setup`, `ray_pick_tex`.
- Doors: `parse_doors`, `doors_update`, `door_blocks_cell`, `door_plane_offset`, `apply_door_sink`, `ray_find_wall_behind_door`, `draw_slice`.
- Collectibles: `collectibles.c`, `keys_load.c`, `collectibles_update.c`, `collectibles_draw.c`.
- Minimap: `minimap.c`, `minimap_sampling.c`, `minimap_utils.c`, `minimap_colors.c`.
- Overlays: `game_screen.c`, `game_screen_utils.c`, `game_utils.c`.
- Input: `input/keyboard.c`, `input/mouse.c`.
- Cleanup: `cleanup/cleanup.c`, `cleanup/cleanup_render.c`, `cleanup/util.c`, `cleanup/doors_clean.c`.
</details>
