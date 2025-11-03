# Quickstart: Compiling and Running

## Compilation

The project is compiled using `make`.

```bash
make
```

This will create the executable `miniRT` in the root directory.

## Running

To render a scene, provide the path to a `.rt` scene file as an argument.

```bash
./miniRT scenes/example.rt
```

The output will be an image file named `render.bmp` (or similar), or a window will appear showing the rendered scene.
