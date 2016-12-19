# Overmon
`Overmon` is a grid-based overworld RPG engine library made using `SFML`.

## Compiling
Use `cmake` to compile the project. You must have `SFML` installed on your system.

`Overmon` uses several C++17 features. `CMakeLists.txt` is configured to enable them for GCC and Clang.

## Usage
There are various subprojects:
 - `core` - This is the build of the `Overmon` library. This is always required.
 - `demo` - A demonstration of how to use the library.
 - `explorer` - Viewer applications that shows all maps laid out starting from a base.

## Resources
`Overmon` currently loads all resources dynamically (but a static compilation model will be introduced eventually).

### Sprites
Sprites consist of images that may or may not be animated.

Sprites are loaded from `resources/sprites/manifest.toml`. Below is a sample file:
```toml
[[sprite]]
## These are required:

# Each sprite must have a unique identifier value.
id = 0

# The image file to load. This is relative to this manifest file directory.
file = "player/player_waking.png"

## The following are optional:

# If the image is made up of multiple frames (e.g. animations), then a frame size must be specified.
width = 32
height = 32

# An offset position may be applied for drawing.
offset_x = 8
offset_y = 16
```

### Areas
Areas are made up of `Tiled` `.tmx` files. The `.tmx` parser is currently very limited but should suffice for most situations.

Areas are loaded from `resources/areas/manifest.toml`. Below is a sample file:
```toml
[[area]]
## These are required:

# Each area must have a unique identifier value.
id = 0

# Each area must have a name. This is used for referencing areas and used for display purposes.
name = "Town"

# The `Tiled` file to load from. This is relative to this manifest file directory.
file = "towns/Town.tmx"

# These are optional:

# Boundary areas. These areas will be shown around this area.
north = "Route"
south = "City"
east = "Forest"
west = "Ocean"

# Boundary area offsets. The offset relative to this area.
# North and south offsets are horizontal.
# East and west offsets are vertical.
northOffset = -12
southOffset = 2
eastOffset = 0
eastOffset = 1

# A repeated area used to fill empty spaces, e.g. when there are no bounary areas and in corners.
fill = "Trees"
```

As implied by the `fill` variable, areas do not have specified corner boundaries.

Additionally, adjacent areas must have the same touching size parity. For example, consider an area 17 tiles wide with an area to the north. The north area must have an odd width, e.g. 19. This is because the repeated filled area may not repeat correctly otherwise.

## Transpiling
__NOTE: This section describes functionality that is planned and does not exist.__

The `transpiler` subproject takes all resources and turns them into C++ code.

The most basic operation is transforming all resources are transformed into C++ `enum`s to improve referencing resources in projects. This is always done, even with dynamically loaded resources.

### Static Resources
Static resources are transformed into array literals through a variety of different methods:
 - __Sounds__: The most straight-forward. They are simply reformatted and saved as a common format.
 - __Sprites__: Similar to sounds except they are optimized by being batched.
 - __Areas__: Uses a completely custom array literal format that optimizes against texture swapping.
