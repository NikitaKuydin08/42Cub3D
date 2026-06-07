# cub3D — Project Progress

> 42 cub3D project: 3D first-person maze game using raycasting

---

## ✅ MANDATORY FEATURES (COMPLETED)

### Parsing & Validation

- [x] File access checks (`.cub` ext, regular file, openable, non-empty)
- [x] Read full map configuration file into memory
- [x] Parse map header: textures (NO/SO/EA/WE), sprite (S), colors (F/C)
- [x] Texture path validation (PNG files must exist)
- [x] Floor/Ceiling RGB color validation (0-255 range)
- [x] Build 2D map grid from `.cub` file
- [x] Reject invalid characters in map (only 0, 1, N, S, E, W allowed + spaces)

### Map Validation

- [x] Single player spawn check (exactly one N/S/E/W character)
- [x] Player positioning check (must be surrounded by walkable space)
- [x] Map closure validation (must be completely surrounded by walls)
- [x] Detect wall holes and unreachable areas
- [x] Handle ragged map arrays safely

### Memory Management

- [x] No memory leaks in parser (validated with valgrind)
- [x] Proper cleanup on error paths
- [x] Zero-initialization of data structures

### Graphics Rendering (MLX42)

- [x] Window creation and event handling
- [x] Floor/ceiling color rendering
- [x] Wall texture loading from PNG files (NO/SO/EA/WE)
- [x] Raycasting algorithm implementation:
  - Per-column DDA ray-casting
  - Horizontal/vertical wall intersection detection
  - Distance calculation (perpendicular to eliminate fisheye)
  - Texture mapping (X from wall hit, Y from column position)
- [x] Textured wall rendering to screen

### Player & Input

- [x] Player initialization from map spawn point
- [x] Movement controls: W/A/S/D (translate along/perpendicular to direction)
- [x] Rotation controls: LEFT/RIGHT arrows (rotate direction vector)
- [x] Wall collision detection during movement
- [x] ESC key and window close button for clean exit
- [x] Smooth real-time input handling

---

## 🔧 BONUS FEATURES

### In Progress / Planned

- [ ] **Minimap rendering** — Draw 2D top-down view of map with player position and direction
  - Show walkable spaces (0), walls (1), player FOV cone
  - Update in real-time as player moves/rotates
  - Render at fixed screen corner (e.g., top-right)

- [ ] **Mouse rotation** — Look around by moving the mouse
  - Capture mouse movement and rotate player view
  - Smooth camera control via mouse delta
  - Optional mouse lock mode

- [ ] Wall sprites (if time permits)
- [ ] Advanced lighting effects
- [ ] Performance optimizations

---

## 🧪 Testing & Debugging

- [x] Valgrind leak suppression file (`mlx.supp`)
  - Suppresses: MLX, X11, LLVM, GPU driver, OpenGL, Mesa, libc loader leaks
  - Focuses testing on actual code leaks
- [x] Memory leak test suite (`cub3D_leaks_maps_tester`)
  - 184 invalid map test cases
  - PNG texture support (converted from XPM)
  - Clean valgrind pass with 0 bytes definitely lost

---

## 📊 Project Statistics

- **Parser**: Fully validated and tested
- **Rendering**: Raycasting + textured walls complete
- **Input**: All mandatory controls working
- **Memory**: Clean (0 leaked bytes from code)
- **Status**: Mandatory features ✅ | Ready for bonus features