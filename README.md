# pbase
Base library for 3D stuff, like pointc, visu, ...


## Visu
My library [Visu](https://github.com/renehorstmann/Visu) uses pbase as its base library.
Visu uses OpenGL to render point clouds, meshes, etc.

SVisu is a simple version to quickly show a point cloud in code for debugging.


## Getting started

### Install
Should work on Unix (Ubuntu) and msys2/mingw (Windows).
```sh
# in the pbase dir:
mkdir build && cd build
cmake ..
make
make install # or sudo make install
```
On Unix, the library will be installed in /usr/local/
On Windows, it will be installed in C:/Libraries/
If using Windows, add C:/Libraries/lib to your PATH, so cmake can find libpbase.so

If you want to install the python bindings as well, set the env variable:
`PYTHON_LIB_INSTALL_DIR`
to the destination, in which the bindings should be installed

### Usage
To use pbase in your cmake project:
```cmake
cmake_minimum_required(VERSION 3.0)
project(pbasetest C)

set(CMAKE_C_STANDARD 11)

add_executable(main main.c)

if (MINGW) # windows
  include_directories("C:/Libraries/include")
endif()

find_library(PBASE_LIB pbase)
target_link_libraries(main ${PBASE_LIB})
```

### Example
[example_convert.c](tests/example_convert.c) loads an stl mesh and saves it as ply mesh
```c
#include <stdio.h>
#include <stdlib.h>
#include <pbase/pbase.h>

int main(int argc, char **argv) {
    if (argc < 3 || argc > 4) {
        printf("Usage: %s <load_mesh.stl> <save_mesh.ply> [ascii=0]", argv[0]);
        exit(EXIT_FAILURE);
    }

    bool ascii = false;
    if(argc==4 && *argv[3]=='1') {
        puts("saving as ascii ply");
        ascii = true;
    }

    pCloud points;
    pMeshIndices indices;
    p_io_load_mesh_stl(&points, &indices, argv[1]);

    p_io_save_mesh_ply(points, indices, argv[2], ascii);

    if(p_error()) {
        printf("An error occured while converting: %s", p_error());
        exit(EXIT_FAILURE);
    }

    p_cloud_kill(&points);
    p_mesh_indices_kill(&indices);
    exit(EXIT_SUCCESS);
}
```

[example_convert.py](python/example_convert.py) does the same as above, but in python:
```python
import sys
import pbase as p

if __name__ == '__main__':
    if len(sys.argv) < 3 or len(sys.argv) > 4:
        print('Usage:', sys.argv[0], '<load_mesh.stl> <save_mesh.ply> [ascii=0]')
        exit(1)
        
    ascii = False
    if len(sys.argv) == 4 and sys.argv[3] == '1':
        print('saving as ascii ply')
        ascii = True
        
    points, indices = p.io.load_mesh_stl(sys.argv[1])
    p.io.save_mesh_ply(points, indices, sys.argv[2], ascii)
```


## types
Base classes for 3D stuff
 - `pCloud` point cloud (list of `vec4`)
 - `pIndices` indices (list of `int`)
 - `pIndicesList` list of `pIndices`
 - `pMeshIndices` list of triangles (list of `ivec3`)
 - `pMatrix` matrix of floats
 - `pVector` vector of floats

## error
Error management is based on rhc

`p_error` returns a string with the error code, or NULL if no error occured

`p_error_set` sets and returns an error

Functions can set an error and should return invalid data (e. g. `p_cloud_new_invalid`) or return `p_error`

## io
 - load and save stl files (Mesh)
 - load and save ply files (PointClouds (with normals and or colors), Meshs (with normals and or colors))
 - load and save csv files (Indices, IndicesList, Matrix, Vector)
see [example_convert.c](tests/example_convert.c) for an stl to ply converter.

## meshprimitives
Generates meshs:
 - plane
 - box
 - sphere
 - half_sphere
 - cylinder
 - cone
 - arrow

## RHC
based on my [rhc](https://github.com/renehorstmann/rhc) library.
Contains some useful stuff for C programming
 - allocators
 - error
 - log
 - dynarray
 - ...
All globals are renamed from `rhc_*` to `p_rhc_*`

## Mathc
based on my [Mathc](https://github.com/renehorstmann/Mathc) library.
Linear algebra types and functions in a glsl style
 - vec3
 - vec4
 - mat4
 - ...


## Todo
- visu
  - README.md
- pointc
  - uses flann
  - does not use pcl
    - normals
    - sac
    - icp
    - mesh
- collisionc?
  - capsule
  - mesh - cloud?
- robotc?
  - fk
  - ik
  - some robots
  - cell?
  - abb connection

## Author

René Horstmann

## Licence

This project is licensed under the MIT License - see the LICENSE file for details

