# pbase
Base library for 3D stuff, like pointc, visu, ...


## Visu
My library [Visu](https://github.com/renehorstmann/Visu) uses pbase as its base library.
Visu (OpenGL based) is used for rendering point clouds, meshes, etc.

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

### How to read the code
- Have a look at some examples
- Get used to [rhc](https://github.com/renehorstmann/rhc) and [Mathc](https://github.com/renehorstmann/Mathc)
- Read the (hopefully) self explaining header files, I tried to let the header interface be as simple as possible
  - Function parameter called `out_*` are output parameters
  - Method parameter called `self` indicate classes
- If you are using the Python bindings, also have a look at the C header files
  - `out_*` parameter are returned
  - Most types and classes are wrapped in numpy arrays (dtype is usally float32, int32)
  - Errors are raised as RunTimeErros (Exceptions)
  - Namespaces are modules: `p_io_load_mesh_stl` will be `p.io.load_mesh_stl`
  - Base class methods are in the module `types`
  - `*_kill` will be called automatically
- have fun

### Example
The following example program will simply load an .stl mesh and save it as a .ply mesh.

#### C
[example_convert.c](tests/example_convert.c)
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

#### Python3
[example_convert.py](python/example_convert.py)
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

#### Type creation
To create a cloud, use the `*_new` methods, or use your own data
```c
// creates an empty (uninitialized) point cloud with 10 points
// each point is a vec4 (4*float)
pCloud points = p_cloud_new_empty(10);

// fill data
for(int i=0; i<points.size; i++) {
    // w=1 for points
    // w=0 for vectors
    points.data[i] = (vec4) {{i, i*i, i*i*i, 1}};
}

// prints the min values for x, y, z and w
vec4 min = p_cloud_min(points);
vec4_println(min);

// free the memory
p_cloud_kill(&points);

// pCloud from own data
float data[2][4] = {
    {1, 2, 3, 0},
    {4, 5, 6, 0}
};
pCloud normals = {
    .data = (vec4*) data, 
    .size = 2
};

// prints the max values for x, y, z and w
vec4 max = p_cloud_max(normals);
vec4_println(max);

// do not free/kill your casted pCloud!
```

In Python, most types are represented by numpy arrays.
```python
import pbase as p
import numpy as np

points = np.empty((10, 4), dtype=np.float32)
for i in range len(points):
    points[i] = [i, i**2, i**3, 1]

print(p.types.cloud_min(points))

# If you get a cloud returned by a pbase function,
# it will be automatically killed by the NpCloud class
```

## Style
pbase and all its libraries (Visu, Pointc, ...) are written using [rhc style](https://github.com/renehorstmann/rhc/blob/main/style.md).

## Modules
Have a look at the headers in include/pbase for more (self explaining) infos.

### types
Base classes for 3D stuff
 - `pCloud` point cloud (list of `vec4`)
 - `pIndices` indices (list of `int`)
 - `pIndicesList` list of `pIndices`
 - `pMeshIndices` list of triangles (list of `ivec3`)
 - `pMatrix` matrix of floats
 - `pVector` vector of floats

### error
Error management is based on rhc

`pError p_error()` returns a string with the error code, or NULL if no error occured

`pError p_error_set(pError set)` sets and returns an error

Functions can set an error and should return invalid data (e. g. `p_cloud_new_invalid()`) or return `p_error()`

### io
 - load and save stl files (Mesh)
 - load and save ply files (PointClouds (with normals and or colors), Meshs (with normals and or colors))
 - load and save csv files (Indices, IndicesList, Matrix, Vector)

see [example_convert.c](tests/example_convert.c) for an stl to ply converter.

### meshprimitives
Generates meshs:
 - plane
 - box
 - sphere
 - half_sphere
 - cylinder
 - cone
 - arrow

### RHC
based on my [rhc](https://github.com/renehorstmann/rhc) library.
Contains some useful stuff for C programming.
 - allocators
 - error
 - log
 - dynarray
 - ...
All globals are renamed from `rhc_*` to `p_rhc_*`

### Mathc
based on my [Mathc](https://github.com/renehorstmann/Mathc) library.
Linear algebra types and functions in a glsl style
 - vec3
 - vec4
 - mat4
 - ...


## Todo
- replace giraffe.stl
- visu
  - use rhc times momotonic
  - remove impl allocations, if possible
    - Impl derives Base as super...
- pointc
  - uses flann
  - capture +LSS
  - does not use pcl
    - normals
    - sac
    - icp
    - mesh
- collisionc
  - capsule
  - mesh - cloud?
- robotc
  - fk
  - ik
  - some robots or generate by dh
  - cell tree
    - Item
      - relative pose
      - offset
      - pose
      - name, etc
  - abb connection

## Author

René Horstmann

## Licence

This project is licensed under the MIT License - see the LICENSE file for details

